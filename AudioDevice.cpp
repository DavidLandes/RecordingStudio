#include "AudioDevice.hpp"

AudioDevice::AudioDevice(QObject *parent)
    : QObject{parent}
    , m_info()
    , m_audioInput(nullptr)
{
}

void AudioDevice::initialize(QAudioDeviceInfo info)
{
    qDebug() << "AudioDevice::initialize() -" << info.deviceName();
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }
    if (m_audioInput != nullptr)
        delete m_audioInput;

    setAudioInput(new QAudioInput(format));
    setInfo(info);
    setName(info.deviceName());
}

bool AudioDevice::isReady()
{
    return m_audioInput != nullptr && m_info.deviceName() != "";
}

QAudioDeviceInfo AudioDevice::info() const
{
    return m_info;
}

void AudioDevice::setInfo(QAudioDeviceInfo newInfo)
{
    if (m_info != newInfo)
    {
        m_info = newInfo;
        emit infoChanged();
    }
}

QAudioInput* AudioDevice::audioInput() const
{
    return m_audioInput;
}

void AudioDevice::setAudioInput(QAudioInput* newAudioInput)
{
    if (m_audioInput != newAudioInput)
    {
        m_audioInput = newAudioInput;
        emit audioInputChanged();
    }
}

QString AudioDevice::name() const
{
    return m_name;
}

void AudioDevice::setName(QString microphoneName)
{
    if (m_name != microphoneName)
    {
        m_name = microphoneName;
        settings.setValue(Settings::Config::MicrophoneName, microphoneName);
        emit nameChanged();
    }
}
