#include "AudioData.hpp"

AudioData::AudioData(QObject *parent)
    : QObject{parent}
{

}

QByteArray AudioData::hex() const
{
    return m_hex;
}

void AudioData::setHex(QByteArray newHex)
{
    if (m_hex != newHex)
    {
        m_hex = newHex;
        emit hexChanged();
    }
}
