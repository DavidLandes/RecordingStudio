#pragma once

#include <QDebug>
#include <QDir>
#include <QObject>
#include <QSettings>

#define RECORDING_GROUP QString("Recording")
#define PLAYBACK_GROUP QString("Playback")

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QString path, QObject *parent = nullptr);

    enum class Config
    {
        RecordDelay,
        MicrophoneName,
    };
    Q_ENUM(Config)

    QVariant value(Config config);
    void setValue(Config config, QVariant newValue);

signals:

private:
    QSettings* m_settings;
};

