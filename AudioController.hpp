#pragma once
#include <QObject>
#include <QSettings>
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
    Q_PROPERTY(Project* currentProject READ currentProject WRITE setCurrentProject NOTIFY currentProjectChanged)
    Q_PROPERTY(QVariantList startDelayOptions READ startDelayOptions NOTIFY startDelayOptionsChanged)
    Q_PROPERTY(int startDelay READ startDelay WRITE setStartDelay NOTIFY startDelayChanged)

    explicit AudioController(QObject *parent = nullptr);
    ~AudioController();

    Recorder* recorder() const;
    void setRecorder(Recorder* recorder);
    Project* currentProject() const;    
    void setCurrentProject(Project* currentProject);
    QVariantList startDelayOptions() const;
    int startDelay() const;
    void setStartDelay(int startDelay);

signals:
    void recorderChanged(Recorder* recorder);
    void currentProjectChanged(Project* currentProject);    
    void startDelayOptionsChanged(QVariantList startDelayOptions);
    void startDelayChanged(int startDelay);

private:
    Recorder* m_recorder;
    Project* m_currentProject;
    QVariantList m_startDelayOptions;
    int m_startDelay;
};
