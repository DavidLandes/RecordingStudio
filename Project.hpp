#pragma once

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileSystemWatcher>
#include <QObject>
#include <QTime>
#include "Globals.hpp"
#include "Track.hpp"

class Project : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QList<Track*> tracks READ tracks NOTIFY tracksChanged)

    explicit Project(QString name, QObject *parent = nullptr);
    ~Project();

    void initProject();
    void loadAudioTracks();
    QStringList getTrackNames();
    Q_INVOKABLE void createTrack();
    Q_INVOKABLE void deleteTrack(int index, bool deleteAudio=true);
    void deleteAllTracks(bool deleteAudio=true);

    Q_INVOKABLE void playAll();
    Q_INVOKABLE void stopAll();

    QString name() const;
    QList<Track*> tracks() const;

public slots:
    void onAudioFileChanged(QString filePath);

signals:
    void nameChanged(QString name);
    void tracksChanged(QList<Track*> tracks);

private:
    QFileSystemWatcher m_fileWatcher;
    const QDir appDir = QDir(QDir::homePath() + "/Documents/RecordingStudio/");
    QDir m_projectDir;
    QDir m_audioDir;
    QString m_name;
    QList<Track*> m_tracks;
};

