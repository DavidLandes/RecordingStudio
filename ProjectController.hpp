#pragma once
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QObject>
#include <QProcess>
#include <QUrl>
#include "Project.hpp"

class ProjectController : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(Project* current READ current WRITE setCurrent NOTIFY currentChanged)
    explicit ProjectController(QObject *parent = nullptr);

    Q_INVOKABLE void open();
    Q_INVOKABLE void create(QString projectName);


    Project* current() const;
    void setCurrent(Project* current);

signals:
    void currentChanged(Project* current);

private:
    const QDir appDir = QDir(QDir::homePath() + "/Documents/RecordingStudio/");
    Project* m_current;
};

