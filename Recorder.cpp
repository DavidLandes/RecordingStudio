#include "Recorder.hpp"

Recorder::Recorder(QObject *parent) : QObject(parent)
  , m_devices({})
  , m_currentRecordingTrack(nullptr)
{
    refreshDevices();
    m_audioDevice = new AudioDevice();
    // Try to set the last device. Otherwise choose the first audio input option available.
    QString lastDevice = settings.value(Settings::Config::MicrophoneName).toString();
    if (lastDevice != "")
    {
        initializeAudioDevice(lastDevice);
    }
    else
    {
        m_audioDevice->initialize(m_devices.first());
    }

    m_recorder = new QAudioRecorder();
    connect(m_recorder, &QAudioRecorder::stateChanged, [=]() { setState(convertState(m_recorder->state())); });

    // Setup timer to collect recording samples.
    m_sampleTimer = new QTimer();
    m_sampleTimer->setInterval(250);
    connect(m_sampleTimer, &QTimer::timeout, [=]() { onRecordingVolumeChanged(m_recorder->volume()); });
}

Recorder::~Recorder()
{
    delete m_recorder;
    delete m_audioDevice;
}

void Recorder::initializeAudioDevice(QString name)
{
    for (QAudioDeviceInfo dev : m_devices)
    {
        if (dev.deviceName() == name)
        {
            m_audioDevice->initialize(dev);
            return;
        }
    }
    qDebug() << "Device" << name << "invalid, cannot initialize";
}

void Recorder::refreshDevices()
{
    m_devices.clear();
    setDevices(QAudioDeviceInfo::availableDevices(QAudio::AudioInput));
}

void Recorder::start(Track* track)
{
    if (m_audioDevice->isReady() && QFile::exists(track->source()->filePath()))
    {
        m_currentRecordingTrack = track;

        // Start recording.
        m_recordingDevice = m_audioDevice->audioInput()->start();

        // Track recording volume.
        m_currentRecordingTrack->setVolumeSamples({});
        m_sampleTimer->start();
        qDebug() << "Recording Start:" << m_recorder->errorString();
    }
    else
    {
        qDebug() << "Cannot start recording for file:" << track->source()->filePath();
    }
}

void Recorder::stop()
{
    if (m_audioDevice->isReady())
    {
        // Save bytes to the output file.
        QFile output(m_currentRecordingTrack->source()->filePath());
        output.open(QIODevice::WriteOnly);
        output.write(m_recordingDevice->readAll());

        m_sampleTimer->stop();
        m_currentRecordingTrack = nullptr;
        qDebug() << "Recording Stop:";
    }
    else
    {
        qDebug() << "Cannot stop recording. Device is not ready:" << m_audioDevice;
    }
}

QList<QAudioDeviceInfo> Recorder::devices() const
{
    return m_devices;
}

void Recorder::setDevices(QList<QAudioDeviceInfo> inputs)
{
    if (m_devices != inputs)
    {
        m_devices = inputs;
        emit devicesChanged(inputs);
        emit deviceNamesChanged();
    }
}

Recorder::State Recorder::state() const
{
    return m_state;
}

bool Recorder::isRecording() const
{
    return m_state == Recorder::State::Recording;
}

void Recorder::onRecordingVolumeChanged(qreal volume)
{
    if (m_currentRecordingTrack && isRecording())
    {
        QList<float> samples = m_currentRecordingTrack->volumeSamples();
        samples.append(1);
        m_currentRecordingTrack->setVolumeSamples(samples);
    }
}

Recorder::State Recorder::convertState(QMediaRecorder::State state)
{
    switch(state)
    {
    case QMediaRecorder::State::StoppedState:
        return Recorder::State::Stopped;
    case QMediaRecorder::State::RecordingState:
        return Recorder::State::Recording;
    case QMediaRecorder::State::PausedState:
        return Recorder::State::Paused;
    default:
        return Recorder::State::Stopped;
    }
}

void Recorder::setState(Recorder::State state)
{
    if (m_state != state)
    {
        m_state = state;
        emit stateChanged(m_state);
    }
}

QStringList Recorder::deviceNames() const
{
    QStringList names = {};
    for (QAudioDeviceInfo device : m_devices)
    {
        names.append(device.deviceName());
    }
    return names;
}

AudioDevice *Recorder::audioDevice() const
{
    return m_audioDevice;
}

void Recorder::setAudioDevice(AudioDevice *newAudioDevice)
{
    if (m_audioDevice != newAudioDevice)
    {
        m_audioDevice = newAudioDevice;
        emit audioDeviceChanged();
    }
}
