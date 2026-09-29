#include "playercontroller.h"
#include <QFileInfo>
#include <QUrl>

PlayerController::PlayerController(QObject *parent)
    : QObject(parent),
      m_player(new QMediaPlayer(this)),
      m_audioOutput(new QAudioOutput(this))
{
    m_player->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.7f); // 預設音量 70%

    connect(m_player, &QMediaPlayer::playbackStateChanged, this, &PlayerController::isPlayingChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &PlayerController::positionChanged);
    connect(m_player, &QMediaPlayer::durationChanged, this, &PlayerController::durationChanged);
}

void PlayerController::playPause()
{
    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        m_player->pause();
    } else {
        m_player->play();
    }
}

void PlayerController::playTrack(const QString &filePath)
{
    m_player->setSource(QUrl::fromLocalFile(filePath));
    m_currentTrackTitle = QFileInfo(filePath).fileName();
    emit trackChanged();
    m_player->play();
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
