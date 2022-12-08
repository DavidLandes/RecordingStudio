#include "AudioDevice.hpp"

AudioDevice::AudioDevice(QObject *parent)
    : QObject{parent}
    , m_info()
    , m_input(nullptr)
{
    // Default audio format
    QAudioFormat format;
    format.setSampleRate(11025);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    setFormat(format);
}

void AudioDevice::initialize(QAudioDeviceInfo info)
{
    qDebug() << "AudioDevice::initialize() -" << info.deviceName();

    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        info.nearestFormat(m_format);
    }

    // Set the audio input. Notify when we should read audio data.
    QAudioInput* newInput = new QAudioInput(m_format);
    newInput->setNotifyInterval(100);
    setInput(newInput);
    setInfo(info);
    setName(info.deviceName());
}

bool AudioDevice::isReady()
{
    return m_input != nullptr && m_info.deviceName() != "";
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

QAudioInput* AudioDevice::input() const
{
    return m_input;
}

void AudioDevice::setInput(QAudioInput* newInput)
{
    if (newInput != nullptr)
    {
        if (m_input != nullptr)
        {
            delete m_input;
        }
        m_input = newInput;
        emit inputChanged();
    }
    else
    {
        qDebug() << "Warning: Tried to set AudioInput to nullptr";
    }
}

QString AudioDevice::name() const
{
    return m_name;
}

QAudioFormat AudioDevice::format() const
{
    return m_format;
}

void AudioDevice::setFormat(QAudioFormat format)
{
    if (m_format != format)
    {
        m_format = format;
        emit formatChanged();
    }
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
