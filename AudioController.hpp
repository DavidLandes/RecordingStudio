#pragma once
#include <QAudioDeviceInfo>
#include <QObject>
#include "AudioParser.hpp"
#include "Globals.hpp"
#include "Player.hpp"
#include "Project.hpp"
#include "Recorder.hpp"
#include "Track.hpp"


class AudioController : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(Recorder* recorder READ recorder WRITE setRecorder NOTIFY recorderChanged)
    Q_PROPERTY(QList<QAudioDeviceInfo> devices READ devices WRITE setDevices NOTIFY devicesChanged)
    Q_PROPERTY(QStringList deviceNames READ deviceNames NOTIFY deviceNamesChanged)
    Q_PROPERTY(Project* currentProject READ currentProject WRITE setCurrentProject NOTIFY currentProjectChanged)
    Q_PROPERTY(QVariantList startDelayOptions READ startDelayOptions NOTIFY startDelayOptionsChanged)
    Q_PROPERTY(int startDelay READ startDelay WRITE setStartDelay NOTIFY startDelayChanged)

    explicit AudioController(QObject *parent = nullptr);
    ~AudioController();

    // Get/set the object used to manage recording audio.
    Recorder* recorder() const;
    void setRecorder(Recorder* recorder);
    // Get/set the current project.
    Project* currentProject() const;    
    void setCurrentProject(Project* currentProject);
    // Get a list of time options for the start delay.
    QVariantList startDelayOptions() const;
    // Get/set the time in seconds between pressing the record button & actually recording audio.
    int startDelay() const;
    void setStartDelay(int startDelay);
    // Get/set the list of available audio input devices
    QList<QAudioDeviceInfo> devices() const;
    void setDevices(QList<QAudioDeviceInfo> newDevices);
    // Returns a list of all audio input device names.
    QStringList deviceNames() const;
    // Refresh the list of available input devices.
    Q_INVOKABLE void refreshDevices();
    // Initialize the audio input device with given name. If the name is not valid, nothing will happen.
    Q_INVOKABLE void initializeAudioDevice(QString name);
    void initializeAudioDevice(QAudioDeviceInfo device);
    // Get the current audio input device. This is an alias for m_recorder.audioDevice();
    Q_INVOKABLE AudioDevice* currentAudioDevice();

signals:
    void recorderChanged(Recorder* recorder);
    void currentProjectChanged(Project* currentProject);    
    void startDelayOptionsChanged(QVariantList startDelayOptions);
    void startDelayChanged(int startDelay);
    void devicesChanged();
    void deviceNamesChanged();

private:
    AudioParser* m_parser;
    Recorder* m_recorder;
    Project* m_currentProject;
    QVariantList m_startDelayOptions;
    int m_startDelay;
    QList<QAudioDeviceInfo> m_devices;
    QStringList m_deviceNames;
};
