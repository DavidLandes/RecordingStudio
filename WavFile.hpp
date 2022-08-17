#pragma once

#include <QObject>
#include "AudioParser.hpp"

class WavFile : public AudioParser
{
    Q_OBJECT
public:
    Q_PROPERTY(WavHeader metaData READ metaData NOTIFY metaDataChanged)
    Q_PROPERTY(QString filePath READ filePath NOTIFY filePathChanged)
    Q_PROPERTY(double duration READ duration NOTIFY durationChanged)

    explicit WavFile(QString filePath, QObject *parent = nullptr);

    void reload();

    const WavHeader &metaData() const;
    const QString &filePath() const;
    double duration() const;

signals:
    void metaDataChanged();
    void filePathChanged();
    void durationChanged();

private:
    WavHeader m_metaData;
    QString m_filePath;
    double m_duration;
};

