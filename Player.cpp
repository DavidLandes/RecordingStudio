#include "Player.hpp"

Player::Player(QObject *parent) : QObject(parent)
  , m_devices({})
  , m_selectedDevice("")
{
    m_player = new QMediaPlayer();
}

Player::~Player()
{

}

void Player::refreshDevices()
{

}

void Player::play(QList<Track *> tracks)
{

}

void Player::pause()
{

}

void Player::stop()
{

}

QStringList Player::devices() const
{
    return m_devices;
}

QString Player::selectedDevice() const
{
    return m_selectedDevice;
}

void Player::setDevices(QStringList devices)
{
    if (m_devices == devices)
        return;

    m_devices = devices;
    emit devicesChanged(m_devices);
}

void Player::setSelectedDevice(QString selectedDevice)
{
    if (m_selectedDevice == selectedDevice)
        return;

    m_selectedDevice = selectedDevice;
    emit selectedDeviceChanged(m_selectedDevice);
}
