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
    Q_PROPERTY(QList<QAudioDeviceInfo> devices READ devices WRITE setDevices NOTIFY devicesChanged)
    Q_PROPERTY(QStringList deviceNames READ deviceNames NOTIFY deviceNamesChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
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

    Q_INVOKABLE void refreshDevices();
    Q_INVOKABLE void start(Track* track);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void initializeAudioDevice(QString name);

    QList<QAudioDeviceInfo> devices() const;
    void setDevices(QList<QAudioDeviceInfo> inputs);
    State state() const;    
    bool isRecording() const;
    QStringList deviceNames() const;
    AudioDevice *audioDevice() const;
    void setAudioDevice(AudioDevice *newAudioDevice);

signals:
    void devicesChanged(QList<QAudioDeviceInfo> inputs);
    void stateChanged(State state);
    void deviceNamesChanged();
    void audioDeviceChanged();

public slots:
    void onRecordingVolumeChanged(qreal volume);

private:
    State convertState(QAudioRecorder::State state);
    void setState(State state);

    QAudioRecorder* m_recorder;
    QList<QAudioDeviceInfo> m_devices;
    State m_state;
    Track* m_currentRecordingTrack;
    QTimer* m_sampleTimer;
    QIODevice* m_recordingDevice;
    AudioDevice *m_audioDevice;
};

