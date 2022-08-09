#pragma once

#include <QObject>
#include <QMediaPlayer>
#include "Track.hpp"

class Player : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QStringList devices READ devices WRITE setDevices NOTIFY devicesChanged)
    Q_PROPERTY(QString selectedDevice READ selectedDevice WRITE setSelectedDevice NOTIFY selectedDeviceChanged)
    explicit Player(QObject *parent = nullptr);
    ~Player();

    Q_INVOKABLE void refreshDevices();
    Q_INVOKABLE void play(QList<Track*> tracks);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

    QStringList devices() const;
    void setDevices(QStringList devices);
    QString selectedDevice() const;
    void setSelectedDevice(QString selectedDevice);

signals:
    void devicesChanged(QStringList devices);
    void selectedDeviceChanged(QString selectedDevice);

private:
    QMediaPlayer* m_player;
    QStringList m_devices;
    QString m_selectedDevice;
};

