#pragma once
#include <QObject>
#include "Player.hpp"
#include "Project.hpp"
#include "Recorder.hpp"
#include "Track.hpp"


class AudioController : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(Recorder* recorder READ recorder WRITE setRecorder NOTIFY recorderChanged)
    Q_PROPERTY(Project* currentProject READ currentProject WRITE setCurrentProject NOTIFY currentProjectChanged)

    explicit AudioController(QObject *parent = nullptr);
    ~AudioController();

    Recorder* recorder() const;
    void setRecorder(Recorder* recorder);

    Project* currentProject() const;

public slots:
    void setCurrentProject(Project* currentProject);

signals:
    void recorderChanged(Recorder* recorder);
    void currentProjectChanged(Project* currentProject);

private:
    Recorder* m_recorder;
    Project* m_currentProject;
};
