#include "playercontroller.h"
#include <QFileInfo>
#include <QImage>
#include <QBuffer>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

PlayerController::PlayerController(QObject *parent)
    : QObject(parent),
      m_player(new QMediaPlayer(this)),
      m_audioOutput(new QAudioOutput(this))
{
    m_player->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.7f);

    connect(m_player, &QMediaPlayer::playbackStateChanged, this, &PlayerController::isPlayingChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &PlayerController::positionChanged);
    connect(m_player, &QMediaPlayer::durationChanged, this, &PlayerController::durationChanged);
    connect(m_player, &QMediaPlayer::metaDataChanged, this, &PlayerController::updateMetaData);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &PlayerController::handleMediaStatusChanged);

    // 初始化 IPC 本地 Socket 服務
    setupIpcServer();
}

PlayerController::~PlayerController()
{
    if (m_ipcServer) {
        m_ipcServer->close();
    }
}

void PlayerController::setupIpcServer()
{
    const QString socketName = "/tmp/pi_agent_mp3.sock";
    
    // 如果舊的 Socket 殘留，先清理掉
    QLocalServer::removeServer(socketName);

    m_ipcServer = new QLocalServer(this);
    connect(m_ipcServer, &QLocalServer::newConnection, this, &PlayerController::handleNewConnection);

    if (m_ipcServer->listen(socketName)) {
        qDebug() << "[IPC Server] Listening on" << socketName;
    } else {
        qWarning() << "[IPC Server] Failed to start:" << m_ipcServer->errorString();
    }
}

void PlayerController::handleNewConnection()
{
    while (m_ipcServer->hasPendingConnections()) {
        QLocalSocket *clientSocket = m_ipcServer->nextPendingConnection();
        connect(clientSocket, &QLocalSocket::readyRead, this, &PlayerController::handleSocketReadyRead);
        connect(clientSocket, &QLocalSocket::disconnected, clientSocket, &QLocalSocket::deleteLater);
    }
}

void PlayerController::handleSocketReadyRead()
{
    auto *socket = qobject_cast<QLocalSocket*>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[IPC] Received invalid JSON:" << parseError.errorString();
        return;
    }

    processIpcCommand(doc.object(), socket);
}

void PlayerController::processIpcCommand(const QJsonObject &jsonObj, QLocalSocket *socket)
{
    QString action = jsonObj["action"].toString();
    QJsonObject response;

    qDebug() << "[IPC Received Action]:" << action;

    if (action == "play_track") {
        QString path = jsonObj["path"].toString();
        if (!path.isEmpty()) {
            addFilesToPlaylist({ QUrl::fromLocalFile(path) });
            playAtIndex(m_playlist.size() - 1);
            response["status"] = "ok";
            response["message"] = "Playing track: " + path;
        } else {
            response["status"] = "error";
            response["message"] = "Path missing";
        }
    } else if (action == "play_pause") {
        playPause();
        response["status"] = "ok";
        response["isPlaying"] = isPlaying();
    } else if (action == "next") {
        nextTrack();
        response["status"] = "ok";
    } else if (action == "previous") {
        previousTrack();
        response["status"] = "ok";
    } else if (action == "set_volume") {
        double vol = jsonObj["volume"].toDouble(0.7);
        setVolume(static_cast<float>(vol));
        response["status"] = "ok";
        response["volume"] = volume();
    } else if (action == "get_status") {
        response["status"] = "ok";
        response["isPlaying"] = isPlaying();
        response["currentTrackTitle"] = m_currentTrackTitle;
        response["currentArtist"] = m_currentArtist;
        response["volume"] = volume();
    } else {
        response["status"] = "error";
        response["message"] = "Unknown action: " + action;
    }

    if (socket && socket->isOpen()) {
        socket->write(QJsonDocument(response).toJson(QJsonDocument::Compact));
        socket->flush();
    }
}

void PlayerController::playPause()
{
    if (m_playlist.isEmpty()) return;

    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        m_player->pause();
    } else {
        if (m_currentIndex < 0 && !m_playlist.isEmpty()) {
            playAtIndex(0);
        } else {
            m_player->play();
        }
    }
}

void PlayerController::setVolume(float volume)
{
    if (qFuzzyCompare(m_audioOutput->volume(), volume)) return;
    m_audioOutput->setVolume(volume);
    emit volumeChanged();
}

void PlayerController::setPosition(qint64 position)
{
    m_player->setPosition(position);
}

void PlayerController::addFilesToPlaylist(const QList<QUrl> &urls)
{
    bool wasEmpty = m_playlist.isEmpty();

    for (const QUrl &url : urls) {
        QString localPath = url.isLocalFile() ? url.toLocalFile() : url.toString();
        
        QVariantMap item;
        item["fileUrl"] = url.toString();
        item["title"] = QFileInfo(localPath).fileName();
        item["artist"] = "未知歌手";
        m_playlist.append(item);
    }

    emit playlistChanged();

    if (wasEmpty && !m_playlist.isEmpty()) {
        playAtIndex(0);
    }
}

void PlayerController::playAtIndex(int index)
{
    if (index < 0 || index >= m_playlist.size()) return;

    m_currentIndex = index;
    emit currentIndexChanged();

    QVariantMap item = m_playlist[index].toMap();
    QUrl fileUrl(item["fileUrl"].toString());

    m_player->setSource(fileUrl);
    
    QString localPath = fileUrl.isLocalFile() ? fileUrl.toLocalFile() : fileUrl.toString();
    m_currentTrackTitle = QFileInfo(localPath).fileName();
    m_currentArtist = "載入標籤中...";
    m_coverArtUrl = "qrc:/qml/default_cover.svg";
    
    emit trackChanged();
    emit coverArtUrlChanged();

    m_player->play();
}

void PlayerController::nextTrack()
{
    if (m_playlist.isEmpty()) return;
    int nextIdx = (m_currentIndex + 1) % m_playlist.size();
    playAtIndex(nextIdx);
}

void PlayerController::previousTrack()
{
    if (m_playlist.isEmpty()) return;
    int prevIdx = (m_currentIndex - 1 + m_playlist.size()) % m_playlist.size();
    playAtIndex(prevIdx);
}

void PlayerController::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia || status == QMediaPlayer::BufferedMedia) {
        updateMetaData();
    }
    
    if (status == QMediaPlayer::EndOfMedia) {
        nextTrack();
    }
}

void PlayerController::updateMetaData()
{
    QMediaMetaData meta = m_player->metaData();

    QString title = meta.value(QMediaMetaData::Title).toString();
    QString artist = meta.value(QMediaMetaData::Author).toString();
    if (artist.isEmpty()) {
        artist = meta.value(QMediaMetaData::ContributingArtist).toString();
    }
    if (artist.isEmpty()) {
        artist = meta.value(QMediaMetaData::AlbumArtist).toString();
    }

    if (!title.isEmpty()) m_currentTrackTitle = title;
    m_currentArtist = artist.isEmpty() ? "本地音樂" : artist;

    if (m_currentIndex >= 0 && m_currentIndex < m_playlist.size()) {
        QVariantMap item = m_playlist[m_currentIndex].toMap();
        item["title"] = m_currentTrackTitle;
        item["artist"] = m_currentArtist;
        m_playlist[m_currentIndex] = item;
        emit playlistChanged();
    }

    QVariant coverVar = meta.value(QMediaMetaData::CoverArtImage);
    if (!coverVar.isValid()) {
        coverVar = meta.value(QMediaMetaData::ThumbnailImage);
    }

    if (coverVar.isValid()) {
        QImage coverImage = coverVar.value<QImage>();
        if (!coverImage.isNull()) {
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            coverImage.save(&buffer, "PNG");
            m_coverArtUrl = QString("data:image/png;base64,") + byteArray.toBase64();
        }
    } else {
        m_coverArtUrl = "qrc:/qml/default_cover.svg";
    }

    emit trackChanged();
    emit coverArtUrlChanged();
}