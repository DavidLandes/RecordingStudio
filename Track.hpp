#pragma once

#include <QAudioOutput>
#include <QFile>
#include <QMediaPlayer>
#include <QObject>
#include <QTimer>
#include <QUrl>
#include "AudioParser.hpp"
#include "WavFile.hpp"

class Track : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(WavFile* source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int offsetMs READ offsetMs WRITE setOffsetMs NOTIFY offsetMsChanged)
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(quint64 elapsed READ elapsed WRITE setElapsed NOTIFY elapsedChanged)
    explicit Track(QString filePath, QObject *parent = nullptr);
    ~Track();

    Q_INVOKABLE void play(int delaySec=0);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

    // Get/set the offset from the start of the audio.
    int offsetMs() const;
    void setOffsetMs(int offsetMs);
    // Get whether this track is currently playing audio.
    bool isPlaying() const;
    // Get/set the elapsed time of the playback.
    quint64 elapsed() const;
    void setElapsed(quint64 elapsed);

    WavFile *source() const;
    void setSource(WavFile *newSource);

signals:
    // Property changed signals.
    void offsetMsChanged(int offsetMs);    
    void volumeChanged(int volume);    
    void isPlayingChanged(bool isPlaying);
    void elapsedChanged(quint64 elapsed);
    void sourceChanged();

private:
    // QMediaPlayer keeps the source filestream open.. This resets the media player.
    void resetMediaPlayer(QString audioSource="");
    // Set whether this track is currently playing audio.
    void setIsPlaying(bool isPlaying);
    // The offset from the start of the audio.
    int m_offsetMs;
    // Plays media for this track.
    QMediaPlayer* m_media;
    // Specifies the audio output settings.
    QAudioOutput* m_audioOutput;
    // Whether this track is currently playing audio.
    bool m_isPlaying;
    // The elapsed time of the playback.
    quint64 m_elapsed;
    WavFile* m_source;
};

