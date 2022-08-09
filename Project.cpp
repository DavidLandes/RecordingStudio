#include "Project.hpp"

Project::Project(QString name, QObject *parent) : QObject(parent)
  , m_name(name)
{
    initProject();
    loadAudioTracks();
}

Project::~Project()
{
    for (int i = m_tracks.length() - 1; i >= 0; i--)
    {
        Track* t = m_tracks.takeLast();
        qDebug() << t;
        delete t;
    }
    disconnect(&m_fileWatcher, nullptr, nullptr, nullptr);
}

void Project::initProject()
{
    /* Directory Structure
     *  RecordingStudio/
     *      |___myproject1/
     *      |___anotherproject2/
     *          |___audio/
     *              |___track_1.wav
     *              |___track_2.wav
     *              |___track_3.wav
     *              |___track_4.wav
    */
    m_projectDir = QDir(appDir.absolutePath() + "/" + m_name);
    m_audioDir = QDir(m_projectDir.absolutePath() + "/audio");

    // Make sure the appropriate directories exists.
    qDebug() << "Creating app directory -" << (appDir.mkdir(appDir.absolutePath()) || appDir.exists() ? "success" : "failed") << appDir.absolutePath();
    qDebug() << "Creating project directory -" << (m_projectDir.mkdir(m_projectDir.absolutePath()) || m_projectDir.exists() ? "success" : "failed") << m_projectDir.absolutePath();
    qDebug() << "Creating audio directory -" << (m_audioDir.mkdir(m_audioDir.absolutePath()) || m_audioDir.exists() ? "success" : "failed") << m_audioDir.absolutePath();

    // Watch for external file changes & reload them.
    connect(&m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &Project::onAudioFileChanged);
}

void Project::loadAudioTracks()
{
    deleteAllTracks(false);
    for (QString fileName : getTrackNames())
    {
        m_tracks.append(new Track(m_audioDir.absoluteFilePath(fileName)));
        m_fileWatcher.addPath(m_tracks.last()->filePath());
    }
    emit tracksChanged(m_tracks);
}

QStringList Project::getTrackNames()
{
    QStringList typeFilters;
    typeFilters << "*.wav";
    QStringList audioFiles = m_audioDir.entryList(typeFilters, QDir::Filter::Files);
    return audioFiles;
}

void Project::createTrack()
{
    QString fileNameBase = m_audioDir.absolutePath() + "/track_";
    int counter = 1;
    while(1)
    {
        QString newFilePath = fileNameBase + QString::number(counter) + ".wav";
        if (!QFile::exists(newFilePath))
        {
            // Create the track's file.
            QFile newFile(newFilePath);
            newFile.open(QIODevice::ReadWrite);
            newFile.close();
            // Add the new track.
            m_tracks.append(new Track(newFilePath));
            m_fileWatcher.addPath(m_tracks.last()->filePath());
            emit tracksChanged(m_tracks);
            return;
        }
        counter++;
    }
}

void Project::deleteTrack(int index, bool deleteAudio)
{
    if (!m_tracks.isEmpty() && index >= 0 && index < m_tracks.length())
    {
        Track* t = m_tracks.takeAt(index);
        m_fileWatcher.removePath(t->filePath());
        if (deleteAudio)
        {
            QFile::remove(t->filePath());
        }
        delete t;
        emit tracksChanged(m_tracks);
    }
}

void Project::deleteAllTracks(bool deleteAudio)
{
    for (int i = m_tracks.length() - 1; i >= 0; i--)
    {
        deleteTrack(i, deleteAudio);
    }
}

void Project::playAll()
{
    for (Track* track : m_tracks)
    {
        track->play();
    }
}

void Project::stopAll()
{
    for (Track* track : m_tracks)
    {
        track->stop();
    }
}

void Project::onAudioFileChanged(QString filePath)
{
    // A file we were watching was deleted..
    if (!QFile::exists(filePath))
    {
        for (Track* t : m_tracks)
        {
            // If the filePath still exists in the track list, this was deleted externally.. Reload the tracks.
            if (filePath == t->filePath())
            {
                qDebug() << "File deleted externally" << filePath;
                loadAudioTracks();
                break;
            }
        }
    }
}

QString Project::name() const
{
    return m_name;
}

QList<Track *> Project::tracks() const
{
    return m_tracks;
}
