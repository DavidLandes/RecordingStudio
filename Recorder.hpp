#pragma once

#include <QObject>
#include <QAudio>
#include <QAudioInput>
#include <QAudioRecorder>
#include <QDebug>
#include <QDir>
#include <QUrl>
#include "AudioDevice.hpp"
#include "Track.hpp"

class Recorder : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(AudioData* outputData READ outputData WRITE setOutputData NOTIFY outputDataChanged)
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
    Q_INVOKABLE void stop();

    State state() const;    
    bool isRecording() const;
    AudioDevice *audioDevice() const;
    void setAudioDevice(AudioDevice *newAudioDevice);
    // Get/set the audio data from the last recording.
    AudioData *outputData() const;
    void setOutputData(AudioData *newOutputData);

signals:
    void stateChanged(State state);
    void audioDeviceChanged();    
    void outputDataChanged();

private:
    State convertState(QAudioRecorder::State state);
    void setState(State state);

    QAudioRecorder* m_recorder;
    State m_state;
    QIODevice* m_recordingDevice;
    AudioDevice *m_audioDevice;
    AudioData *m_outputData;
};

