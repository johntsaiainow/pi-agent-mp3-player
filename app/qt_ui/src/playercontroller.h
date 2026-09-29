#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class PlayerController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(QString currentTrackTitle READ currentTrackTitle NOTIFY trackChanged)

public:
    explicit PlayerController(QObject *parent = nullptr);

    bool isPlaying() const { return m_player->playbackState() == QMediaPlayer::PlayingState; }
    float volume() const { return m_audioOutput->volume(); }
    qint64 position() const { return m_player->position(); }
    qint64 duration() const { return m_player->duration(); }
    QString currentTrackTitle() const { return m_currentTrackTitle; }

public slots:
    void playPause();
    void playTrack(const QString &filePath);
    void setVolume(float volume);
    void setPosition(qint64 position);

signals:
    void isPlayingChanged();
    void volumeChanged();
    void positionChanged();
    void durationChanged();
    void trackChanged();

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    QString m_currentTrackTitle{"No Track Loaded"};
};

#endif // PLAYERCONTROLLER_H
