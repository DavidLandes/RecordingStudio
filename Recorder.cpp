#include "Recorder.hpp"

Recorder::Recorder(QObject *parent) : QObject(parent)
{
    m_audioDevice = new AudioDevice();
    m_outputData = QByteArray();
    m_recorder = new QAudioRecorder();
    m_inputBuffer = new QBuffer();
    connect(m_recorder, &QAudioRecorder::stateChanged, [=]() { setState(convertState(m_recorder->state())); });
    connect(this, &Recorder::outputDataChanged, [=]() { qDebug() << "output data:" << m_outputData.length(); });
}

Recorder::~Recorder()
{
    delete m_recorder;
    delete m_audioDevice;
    delete m_inputBuffer;
}

void Recorder::start()
{
    // Starting a new recording.. Clear out any outputData.
    setOutputData(QByteArray());
    resume();
}

void Recorder::resume()
{
    if (m_audioDevice->isReady())
    {
        // Start recording.
        m_inputBuffer->close();
        if (m_inputBuffer->open(QIODevice::WriteOnly))
        {
            m_audioDevice->input()->start(m_inputBuffer);
            qDebug() << "Recording Start:" << m_recorder->errorString();
            emit recordingStarted();
        }
        else
        {
            qDebug() << "Cannot record. Input buffer not open";
        }
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
        qDebug() << "Recording Stop";
        m_audioDevice->input()->suspend();
        // Wait for data to finish writing to the buffer before processing it.
        QTimer::singleShot(250, [=]() {
            m_inputBuffer->close();
            processAudioInput();
            emit recordingStopped();
        });
    }
    else
    {
        qDebug() << "Cannot stop recording. Device is not ready:" << m_audioDevice;
    }
}

void Recorder::processAudioInput()
{
    // Append new data to our buffer.
    if (m_inputBuffer->open(QIODevice::ReadOnly))
    {
        m_outputData += m_inputBuffer->readAll();
        m_inputBuffer->close();
        emit outputDataChanged();
    }
    else
    {
        qDebug() << "Error: could not process audio buffer.";
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

QByteArray Recorder::outputData() const
{
    return m_outputData;
}

void Recorder::setOutputData(QByteArray newOutputData)
{
    if (m_outputData != newOutputData)
    {
        m_outputData = newOutputData;
        emit outputDataChanged();
    }
}
