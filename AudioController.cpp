#include "AudioController.hpp"

AudioController::AudioController(QObject *parent) : QObject(parent)
  , m_currentProject(new Project("testProject"))
{
    m_recorder = new Recorder();
    m_recorder->refreshDevices();
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

void AudioController::setCurrentProject(Project *currentProject)
{
    if (m_currentProject == currentProject)
        return;

    m_currentProject = currentProject;
    emit currentProjectChanged(m_currentProject);
}

