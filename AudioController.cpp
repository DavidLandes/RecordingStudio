#include "AudioController.hpp"


AudioController::AudioController(QObject *parent) : QObject(parent)
  , m_currentProject(nullptr)
  , m_startDelayOptions({ 0,1,2,3,4,5 })
{
    m_recorder = new Recorder();
    m_recorder->refreshDevices();
    m_startDelay = settings.value(QString(RECORDING_CONF) + "startDelay", 0).toInt();
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
        settings.setValue(QString(RECORDING_CONF) + "startDelay", startDelay);
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

