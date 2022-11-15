#include "Recorder.hpp"

Recorder::Recorder(QObject *parent) : QObject(parent)
{
    m_audioDevice = new AudioDevice();
    m_outputData = new AudioData();
    m_recorder = new QAudioRecorder();
    connect(m_recorder, &QAudioRecorder::stateChanged, [=]() { setState(convertState(m_recorder->state())); });
}

Recorder::~Recorder()
{
    delete m_recorder;
    delete m_outputData;
    delete m_audioDevice;
}

void Recorder::start()
{
    if (m_audioDevice->isReady())
    {
        // Start recording.
        m_recordingDevice = m_audioDevice->audioInput()->start();
        qDebug() << "Recording Start:" << m_recorder->errorString();
    }
    else
    {
        qDebug() << "Cannot start recording";
    }
}

void Recorder::stop()
{
    if (m_audioDevice->isReady())
    {
        // Save bytes to the output file.
        //TODO: David - We save the recording output into this variable now. All we need to do is create a formatted audio file and insert this data.
        //                Once the file is created, we can attach it to a track & play it.
        m_outputData->setHex(m_recordingDevice->readAll());
        qDebug() << "Recording Stop:" << m_outputData->hex();
    }
    else
    {
        qDebug() << "Cannot stop recording. Device is not ready:" << m_audioDevice;
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

AudioData *Recorder::outputData() const
{
    return m_outputData;
}

void Recorder::setOutputData(AudioData *newOutputData)
{
    if (m_outputData != newOutputData)
    {
        m_outputData = newOutputData;
        emit outputDataChanged();
    }
}
