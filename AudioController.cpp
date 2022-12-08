#include "AudioController.hpp"


AudioController::AudioController(QObject *parent) : QObject(parent)
  , m_currentProject(nullptr)
  , m_startDelayOptions({ 0,1,2,3,4,5 })
  , m_devices({})
{
    m_parser = new AudioParser();
    m_recorder = new Recorder();
    connect(m_recorder, &Recorder::recordingStopped, [=]() {
        m_parser->createWav(m_recorder->audioDevice()->input()->format(), m_recorder->outputData());
    });
    refreshDevices();
    // Try to set the last device. Otherwise choose the first audio input option available.
    QString lastDevice = settings.value(Settings::Config::MicrophoneName).toString();
    if (lastDevice != "")
    {
        initializeAudioDevice(lastDevice);
    }
    else
    {
        initializeAudioDevice(m_devices.first());
    }
    m_startDelay = settings.value(Settings::Config::RecordDelay).toInt();
}

AudioController::~AudioController()
{
    delete m_recorder;
    delete m_currentProject;
}

Recorder *AudioController::recorder() const
{
    return m_recorder;
}

void AudioController::setRecorder(Recorder *recorder)
{
    if (m_recorder == recorder)
        return;

    m_recorder = recorder;
    emit recorderChanged(m_recorder);
}

Project *AudioController::currentProject() const
{
    return m_currentProject;
}

QVariantList AudioController::startDelayOptions() const
{
    return m_startDelayOptions;
}

int AudioController::startDelay() const
{
    return m_startDelay;
}

void AudioController::setStartDelay(int startDelay)
{
    if (m_startDelay != startDelay)
    {
        settings.setValue(Settings::Config::RecordDelay, startDelay);
        m_startDelay = startDelay;
        emit startDelayChanged(m_startDelay);
    }
}

void AudioController::setCurrentProject(Project *currentProject)
{
    if (m_currentProject == currentProject)
        return;

    m_currentProject = currentProject;
    emit currentProjectChanged(m_currentProject);
}

QList<QAudioDeviceInfo> AudioController::devices() const
{
    return m_devices;
}

void AudioController::setDevices(QList<QAudioDeviceInfo> inputs)
{
    if (m_devices != inputs)
    {
        m_devices = inputs;
        emit devicesChanged();
        emit deviceNamesChanged();
    }
}

QStringList AudioController::deviceNames() const
{
    QStringList names = {};
    for (QAudioDeviceInfo device : m_devices)
    {
        names.append(device.deviceName());
    }
    return names;
}

void AudioController::initializeAudioDevice(QString name)
{
    for (QAudioDeviceInfo dev : m_devices)
    {
        if (dev.deviceName() == name)
        {
            // Audio input device is initialized. Make sure the recorder knows when audio data is received.
            m_recorder->audioDevice()->initialize(dev);
            return;
        }
    }
    qDebug() << "Device" << name << "invalid, cannot initialize";
}

void AudioController::initializeAudioDevice(QAudioDeviceInfo device)
{
    m_recorder->audioDevice()->initialize(device);
}

AudioDevice* AudioController::currentAudioDevice()
{
    return m_recorder->audioDevice();
}

void AudioController::refreshDevices()
{
    m_devices.clear();
    setDevices(QAudioDeviceInfo::availableDevices(QAudio::AudioInput));
}
