#pragma once

#include <QAudioOutput>
#include <QFile>
#include <QMediaPlayer>
#include <QObject>
#include <QTimer>
#include <QUrl>

class Track : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString filePath READ filePath WRITE filePath NOTIFY filePathChanged)
    Q_PROPERTY(int offsetMs READ offsetMs WRITE setOffsetMs NOTIFY offsetMsChanged)
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(quint64 duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(quint64 elapsed READ elapsed WRITE setElapsed NOTIFY elapsedChanged)
    explicit Track(QString filePath, QObject *parent = nullptr);

    Q_INVOKABLE void play(int delayMillis=0);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

    // Get/set the name of the audio file for this track.
    QString filePath() const;
    void filePath(QString filePath);
    // Get/set the offset from the start of the audio.
    int offsetMs() const;
    void setOffsetMs(int offsetMs);
    // Get whether this track is currently playing audio.
    bool isPlaying() const;
    // Get/set the duration of the audio track.
    quint64 duration() const;
    void setDuration(quint64 duration);
    // Get/set the elapsed time of the playback.
    quint64 elapsed() const;
    void setElapsed(quint64 elapsed);

signals:
    // Property changed signals.
    void filePathChanged(QString filePath);
    void offsetMsChanged(int offsetMs);    
    void volumeChanged(int volume);    
    void isPlayingChanged(bool isPlaying);
    void durationChanged(quint64 duration);
    void elapsedChanged(quint64 elapsed);

private:
    // QMediaPlayer keeps the source filestream open.. This resets the media player.
    void resetMediaPlayer(QString audioSource="");
    // Set whether this track is currently playing audio.
    void setIsPlaying(bool isPlaying);
    // The name of the audio file for this track.
    QString m_filePath;
    // The offset from the start of the audio.
    int m_offsetMs;
    // Plays media for this track.
    QMediaPlayer* m_media;
    // Specifies the audio output settings.
    QAudioOutput* m_audioOutput;
    // Whether this track is currently playing audio.
    bool m_isPlaying;
    // The duration of the audio track.
    quint64 m_duration;
    // The elapsed time of the playback.
    quint64 m_elapsed;
};

