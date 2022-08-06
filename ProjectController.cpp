#include "ProjectController.hpp"

ProjectController::ProjectController(QObject *parent) : QObject(parent)
  , m_current(nullptr)
{
    setCurrent(new Project("testProject"));
    qDebug() << getProjectNames();
}

void ProjectController::open(QString projectName)
{
    Project* newProject = new Project(projectName);
    if (m_current != nullptr)
        delete m_current;
    setCurrent(newProject);
}

void ProjectController::create(QString projectName)
{
    Project* newProject = new Project(projectName);
    if (m_current != nullptr)
        delete m_current;
    setCurrent(newProject);
}

void ProjectController::erase(QString projectName)
{
    // TODO: show in qml - "Open a project" in workspace when current is nullptr
    for (QString project : getProjectNames())
    {
        if (project == projectName)
        {
            // If this is the current project, delete the project object.
            if (m_current != nullptr && project == m_current->name())
            {
                delete m_current;
                setCurrent(nullptr);
            }
            // Delete the project directory.
            QDir(appDir.absolutePath() + "/" + project).removeRecursively();
            break;
        }
    }
}

QStringList ProjectController::getProjectNames()
{
    QStringList projectDirs = appDir.entryList(QDir::Filter::Dirs | QDir::Filter::NoDot | QDir::Filter::NoDotDot);
    return projectDirs;
}

Project *ProjectController::current() const
{
    return m_current;
}

void ProjectController::setCurrent(Project *current)
{
    if (m_current == current)
        return;

    m_current = current;
    emit currentChanged(m_current);
}
