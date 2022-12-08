#include "AudioParser.hpp"

AudioParser::AudioParser(QObject *parent) : QObject(parent)
{

}

WavHeader AudioParser::parseWav(QString filePath)
{
    QFile audio(filePath);
    if (audio.exists() && audio.open(QIODevice::ReadOnly))
    {
        QByteArray bytes = audio.readAll();
        WavHeader wav = {};
        wav.riff          = decode(bytes, 0, 4, false);
        wav.fileSize      = decode(bytes, 4, 4);
        wav.headerType    = decode(bytes, 8, 4, false);
        wav.formatMarker  = decode(bytes, 12, 4, false);
        wav.formatLen     = decode(bytes, 16, 4);
        wav.formatType    = decode(bytes, 20, 2);
        wav.numOfChannels = decode(bytes, 22, 2);
        wav.sampleRate    = decode(bytes, 24, 4);
        wav.byteRate      = decode(bytes, 28, 4);
        wav.blockAlign    = decode(bytes, 32, 2);
        wav.bitsPerSample = decode(bytes, 34, 2);
        wav.dataHeader    = decode(bytes, 36, 4, false);
        wav.dataSize      = decode(bytes, 40, 4);
        return wav;
    }
    return {};
}

QByteArray AudioParser::createWav(QAudioFormat format, QByteArray data)
{
    qDebug() << "Creating wav file" << data.length();
    QByteArray audioFile;
    WavHeader header = {};
    header.riff          = 0x46464952;  // RIFF
    header.fileSize      = (uint32_t)data.length() + sizeof(WavHeader);   // Data length plus 44 bytes for this header.
    header.headerType    = 0x45564157;  // WAVE
    header.formatMarker  = 0x20746d66;  // fmt
    header.formatLen     = 16; // length of format section above in bytes.
    header.formatType    = (uint16_t)0x1;    // PCM
    header.numOfChannels = (uint16_t)format.channelCount();
    header.sampleRate    = (uint32_t)format.sampleRate();
    header.byteRate      = (uint32_t)(format.sampleRate() * format.sampleSize() * format.channelCount()) / 8;
    header.blockAlign    = (uint16_t)(format.sampleSize() * format.channelCount() / 8);
    header.bitsPerSample = format.sampleSize() * format.channelCount();
    header.dataHeader    = 0x61746164;  // data
    header.dataSize      = (uint32_t)data.length();

    audioFile.append(QByteArray::fromRawData((char*)&header, sizeof(WavHeader)));
    audioFile.append(data);
    return audioFile;
}

quint64 AudioParser::decode(QByteArray bytes, int startByte, int length, bool littleEndian)
{
    quint64 joined = 0;
    int stopByte = startByte + length;
    if (bytes.length() > 0 && inRange(startByte, 0, bytes.length()-1) && inRange(stopByte, 0, bytes.length()-1))
    {
        int counter = littleEndian ? 0 : length-1;
        for (int i = startByte; i < stopByte; i++)
        {
            quint8 byte = bytes[i];
            joined |= byte << (8 * counter);
            counter = littleEndian ? (counter + 1) : (counter - 1);
        }
    }
    return joined;
}

bool AudioParser::inRange(int value, int min, int max)
{
    return value >= min && value <= max;
}
