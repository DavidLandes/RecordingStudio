#include "Settings.hpp"

Settings::Settings(QString path, QObject *parent)
    : QObject{parent}
{
    m_settings = new QSettings(path, QSettings::Format::IniFormat);
}

QVariant Settings::value(Config config)
{
    switch(config)
    {
    case Config::RecordDelay:
        return m_settings->value(RECORDING_GROUP + "/startDelay", 0);
    case Config::MicrophoneName:
        return m_settings->value(RECORDING_GROUP + "/microphoneName", "");
    default:
        qDebug() << "Error: could not get value for config" << config;
        return QVariant();
    }
}

void Settings::setValue(Config config, QVariant newValue)
{
    switch(config)
    {
    case Config::RecordDelay:
        m_settings->setValue(RECORDING_GROUP + "/startDelay", newValue);
        break;
    case Config::MicrophoneName:
        m_settings->setValue(RECORDING_GROUP + "/microphoneName", newValue);
        break;
    default:
        qDebug() << "Error: could not set value for config" << config;
        break;
    }
}

