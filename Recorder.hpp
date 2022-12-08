#pragma once

#include <QObject>
#include <QAudio>
#include <QAudioInput>
#include <QAudioRecorder>
#include <QBuffer>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QThread>
#include <QUrl>
#include "AudioDevice.hpp"
#include "Track.hpp"

class Recorder : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QByteArray outputData READ outputData WRITE setOutputData NOTIFY outputDataChanged)
    Q_PROPERTY(AudioDevice* audioDevice READ audioDevice WRITE setAudioDevice NOTIFY audioDeviceChanged)
    Q_PROPERTY(bool isRecording READ isRecording NOTIFY stateChanged)

    explicit Recorder(QObject *parent = nullptr);
    ~Recorder();

    enum class State
    {
        Stopped,
        Recording,
        Paused,
    };
    Q_ENUM(State)

    Q_INVOKABLE void start();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void stop();
    // Read incoming data from the AudioDevice.
    void processAudioInput();

    State state() const;    
    bool isRecording() const;
    AudioDevice *audioDevice() const;
    void setAudioDevice(AudioDevice *newAudioDevice);
    // Get/set the audio data from the last recording.
    QByteArray outputData() const;
    void setOutputData(QByteArray newOutputData);

signals:
    void stateChanged(State state);
    void audioDeviceChanged();    
    void outputDataChanged();
    void recordingStarted();
    void recordingStopped();

private:
    State convertState(QAudioRecorder::State state);
    void setState(State state);

    QAudioRecorder* m_recorder;
    State m_state;
    QBuffer* m_inputBuffer;
    AudioDevice *m_audioDevice;
    QByteArray m_outputData;
};

