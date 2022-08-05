#pragma once

#include <QObject>

class Track : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString filePath READ filePath WRITE filePath NOTIFY filePathChanged)
    Q_PROPERTY(int offsetMs READ offsetMs WRITE setOffsetMs NOTIFY offsetMsChanged)
    explicit Track(QString filePath, QObject *parent = nullptr);

    // Get/set the name of the audio file for this track.
    QString filePath() const;
    void filePath(QString filePath);
    // Get/set the offset from the start of the audio.
    int offsetMs() const;
    void setOffsetMs(int offsetMs);

signals:
    // Property changed signals.
    void filePathChanged(QString filePath);
    void offsetMsChanged(int offsetMs);

private:
    // The name of the audio file for this track.
    QString m_filePath;
    // The offset from the start of the audio.
    int m_offsetMs;
};

