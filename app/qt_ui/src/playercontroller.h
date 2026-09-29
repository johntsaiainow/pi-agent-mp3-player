#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>
#include <QVariantList>
#include <QUrl>
#include <QLocalServer>
#include <QLocalSocket>

class PlayerController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(QString currentTrackTitle READ currentTrackTitle NOTIFY trackChanged)
    Q_PROPERTY(QString currentArtist READ currentArtist NOTIFY trackChanged)
    Q_PROPERTY(QString coverArtUrl READ coverArtUrl NOTIFY coverArtUrlChanged)
    Q_PROPERTY(QVariantList playlist READ playlist NOTIFY playlistChanged)
    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)

public:
    explicit PlayerController(QObject *parent = nullptr);
    ~PlayerController();

    bool isPlaying() const { return m_player->playbackState() == QMediaPlayer::PlayingState; }
    float volume() const { return m_audioOutput->volume(); }
    qint64 position() const { return m_player->position(); }
    qint64 duration() const { return m_player->duration(); }
    QString currentTrackTitle() const { return m_currentTrackTitle; }
    QString currentArtist() const { return m_currentArtist; }
    QString coverArtUrl() const { return m_coverArtUrl; }
    QVariantList playlist() const { return m_playlist; }
    int currentIndex() const { return m_currentIndex; }

public slots:
    void playPause();
    void setVolume(float volume);
    void setPosition(qint64 position);
    void addFilesToPlaylist(const QList<QUrl> &urls);
    void playAtIndex(int index);
    void nextTrack();
    void previousTrack();

signals:
    void isPlayingChanged();
    void volumeChanged();
    void positionChanged();
    void durationChanged();
    void trackChanged();
    void coverArtUrlChanged();
    void playlistChanged();
    void currentIndexChanged();

private slots:
    void updateMetaData();
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    
    // IPC Socket Slots
    void handleNewConnection();
    void handleSocketReadyRead();

private:
    void setupIpcServer();
    void processIpcCommand(const QJsonObject &jsonObj, QLocalSocket *socket);

    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    QLocalServer *m_ipcServer{nullptr};

    QVariantList m_playlist;
    int m_currentIndex{-1};

    QString m_currentTrackTitle{"未播放曲目"};
    QString m_currentArtist{"未知歌手"};
    QString m_coverArtUrl{"qrc:/qml/default_cover.svg"};
};

#endif // PLAYERCONTROLLER_H