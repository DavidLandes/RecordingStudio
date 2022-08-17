#include "Track.hpp"

Track::Track(QString filePath, QObject *parent) : QObject(parent)
  , m_filePath(filePath)
  , m_offsetMs(0)
  , m_media(nullptr)
  , m_isPlaying(false)
  , m_duration(0)
  , m_elapsed(0)
{
    m_parser = new AudioParser();
    m_parser->parseWav(m_filePath);

    m_audioOutput = new QAudioOutput();
}

void Track::play(int delaySec)
{
    if (QFile::exists(m_filePath))
    {
        resetMediaPlayer(m_filePath);
        setIsPlaying(true);

        // Delay audio playback.
        QTimer::singleShot(delaySec * 1000, this, [=]() {
            m_media->play();
            // Update isPlaying after we try to start the media player. This keeps state in sync if there's an error.
            setIsPlaying(m_media->state() == QMediaPlayer::State::PlayingState);
        });
    }
}

void Track::pause()
{
    if (QFile::exists(m_filePath))
    {
        m_media->pause();
    }
}

void Track::stop()
{
    if (QFile::exists(m_filePath))
    {
        resetMediaPlayer();
        m_media->stop();
    }
}

QString Track::filePath() const
{
    return m_filePath;
}

void Track::filePath(QString fileName)
{
    if (m_filePath != fileName)
    {
        m_filePath = fileName;
        emit filePathChanged(m_filePath);
    }
}

int Track::offsetMs() const
{
    return m_offsetMs;
}

void Track::setOffsetMs(int offsetMs)
{
    if (m_offsetMs != offsetMs)
    {
        m_offsetMs = offsetMs;
        emit offsetMsChanged(m_offsetMs);
    }
}

bool Track::isPlaying() const
{
    return m_isPlaying;
}

quint64 Track::duration() const
{
    return m_duration;
}

quint64 Track::elapsed() const
{
    return m_elapsed;
}

void Track::setDuration(quint64 duration)
{
    if (m_duration == duration)
        return;

    m_duration = duration;
    emit durationChanged(m_duration);
}

void Track::setElapsed(quint64 elapsed)
{
    if (m_elapsed == elapsed)
        return;

    m_elapsed = elapsed;
    emit elapsedChanged(m_elapsed);
}

void Track::resetMediaPlayer(QString audioSource)
{
    if (m_media != nullptr)
    {
        m_media->stop();
        disconnect(m_media, nullptr);
        delete m_media;
        m_media = nullptr;
    }

    m_media = new QMediaPlayer();
    m_media->setMedia(QUrl::fromLocalFile(audioSource));

    // Listen for the media player changes.
    connect(m_media, &QMediaPlayer::durationChanged, this, [=]() { setDuration(m_media->duration()); });
    connect(m_media, &QMediaPlayer::positionChanged, this, [=]() { setElapsed(m_media->position()); });
    connect(m_media, &QMediaPlayer::stateChanged, this, [=]()
    {
        setIsPlaying(m_media->state() == QMediaPlayer::State::PlayingState);
        // Reset the player when it stops.. this frees up the audio file for recording.
        if (m_media->state() == QMediaPlayer::State::StoppedState)
        {
            resetMediaPlayer();
        }
    });
}

void Track::setIsPlaying(bool isPlaying)
{
    if (m_isPlaying == isPlaying)
        return;

    m_isPlaying = isPlaying;
    emit isPlayingChanged(m_isPlaying);
}
