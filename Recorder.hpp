#pragma once

#include <QObject>
#include <QAudio>
#include <QAudioRecorder>
#include <QDir>
#include <QUrl>

class Recorder : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QStringList devices READ devices WRITE setDevices NOTIFY devicesChanged)
    Q_PROPERTY(QString selectedDevice READ selectedDevice WRITE setSelectedDevice NOTIFY selectedDeviceChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
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
    Q_INVOKABLE void start(QString outputPath);
    Q_INVOKABLE void stop();

    QStringList devices() const;
    void setDevices(QStringList devices);
    QString selectedDevice() const;
    void setSelectedDevice(QString selectedDevice);
    State state() const;    
    bool isRecording() const;

signals:
    void devicesChanged(QStringList devices);
    void selectedDeviceChanged(QString selectedDevice);
    void stateChanged(State state);

private:
    State convertState(QAudioRecorder::State state);
    void setState(State state);
    QAudioRecorder* m_recorder;
    QStringList m_devices;
    QString m_selectedDevice;
    State m_state;
};

