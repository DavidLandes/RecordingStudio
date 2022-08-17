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
        qDebug() << wav.bitsPerSample << wav.blockAlign << wav.byteRate << wav.numOfChannels << wav.sampleRate;
        qDebug() << (double)wav.dataSize / wav.byteRate << "seconds";
        return wav;
    }
    return {};
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
