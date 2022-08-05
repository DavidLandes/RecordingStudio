#include "ProjectController.hpp"

ProjectController::ProjectController(QObject *parent) : QObject(parent)
  , m_current(nullptr)
{
    setCurrent(new Project("testProject"));
}

void ProjectController::open()
{
    QProcess* selectDir = new QProcess();
    selectDir->start("explorer.exe", { appDir.absolutePath().replace("/", "\\") });
    selectDir->waitForFinished();
    QString output = selectDir->readAll();
    qDebug() << "open directory:" << output;
    delete selectDir;
}

void ProjectController::create()
{

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
