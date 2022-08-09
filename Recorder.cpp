#include "Recorder.hpp"

Recorder::Recorder(QObject *parent) : QObject(parent)
  , m_devices({})
  , m_selectedDevice("")
{
    m_recorder = new QAudioRecorder();
    connect(m_recorder, &QAudioRecorder::stateChanged, [=]() { setState(convertState(m_recorder->state())); }); // the state isn't changing...
}

Recorder::~Recorder()
{
    delete m_recorder;
}

void Recorder::refreshDevices()
{
    m_devices.clear();
    setDevices(m_recorder->audioInputs());
    // Select the first microphone.
    if (!m_devices.isEmpty())
    {
        setSelectedDevice(m_devices.first());
    }
    qDebug() << m_devices;
}

void Recorder::start(QString outputPath)
{
    if (m_selectedDevice != "" && QFile::exists(outputPath))
    {
        m_recorder->setOutputLocation(QUrl::fromLocalFile(outputPath));
        m_recorder->record();
        qDebug() << "Recording Start:" << m_recorder->errorString();
    }
    else
    {
        qDebug() << "Cannot start recording for file:" << outputPath;
    }
}

void Recorder::stop()
{
    if (m_selectedDevice != "")
    {
        m_recorder->stop();
        qDebug() << "Recording Stop:" << m_recorder->errorString();
    }
}

QStringList Recorder::devices() const
{
    return m_devices;
}

QString Recorder::selectedDevice() const
{
    return m_selectedDevice;
}

void Recorder::setDevices(QStringList microphones)
{
    if (m_devices != microphones)
    {
        m_devices = microphones;
        emit devicesChanged(m_devices);
    }
}

void Recorder::setSelectedDevice(QString selectedMicrophone)
{
    if (m_selectedDevice != selectedMicrophone)
    {
        m_selectedDevice = selectedMicrophone;
        m_recorder->setAudioInput(m_selectedDevice);
        emit selectedDeviceChanged(m_selectedDevice);
    }
}

Recorder::State Recorder::state() const
{
    return m_state;
}

Recorder::State Recorder::convertState(QMediaRecorder::State state)
{
    switch(state)
    {
    case QAudioRecorder::State::StoppedState:
        return Recorder::State::Stopped;
    case QAudioRecorder::State::RecordingState:
        return Recorder::State::Stopped;
    case QAudioRecorder::State::PausedState:
        return Recorder::State::Stopped;
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
