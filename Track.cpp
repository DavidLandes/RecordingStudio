#include "Track.hpp"

Track::Track(QString filePath, QObject *parent) : QObject(parent)
  , m_offsetMs(0)
  , m_media(nullptr)
  , m_isPlaying(false)
  , m_elapsed(0)
  , m_volumeSamples({})
  , m_data(nullptr)
{
    m_audioOutput = new QAudioOutput();
    m_source = new WavFile(filePath);
}

Track::~Track()
{
    delete m_audioOutput;
    delete m_source;
}

void Track::play(int delaySec)
{
    if (QFile::exists(m_source->filePath()))
    {
        resetMediaPlayer(m_source->filePath());
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
    if (QFile::exists(m_source->filePath()))
    {
        m_media->pause();
    }
}

void Track::stop()
{
    if (QFile::exists(m_source->filePath()))
    {
        resetMediaPlayer();
        m_media->stop();
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

quint64 Track::elapsed() const
{
    return m_elapsed;
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
    // Re-parse the audio file metadata.
    m_source->reload();

    // Listen for the media player changes.
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

WavFile *Track::source() const
{
    return m_source;
}

void Track::setSource(WavFile *newSource)
{
    if (m_source == newSource)
        return;
    m_source = newSource;
    emit sourceChanged();
}

QList<float> Track::volumeSamples() const
{
    return m_volumeSamples;
}

void Track::setVolumeSamples(QList<float> newVolumeSamples)
{
    if (m_volumeSamples == newVolumeSamples)
        return;
    m_volumeSamples = newVolumeSamples;
    emit volumeSamplesChanged();
}

QByteArray Track::data() const
{
    return m_data;
}

void Track::setData(QByteArray newData)
{
    if (m_data != newData)
    {
        m_data = newData;
        emit dataChanged();
    }
}
