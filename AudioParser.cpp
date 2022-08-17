#include "AudioParser.hpp"

AudioParser::AudioParser(QObject *parent) : QObject(parent)
{

}

WaveHeader AudioParser::parseWav(QString filePath)
{
    QFile audio(filePath);
    if (audio.exists() && audio.open(QIODevice::ReadOnly))
    {
        QByteArray bytes = audio.readAll();
        WaveHeader wav = {};
        wav.riff          = decode(bytes, 0, 4, false);
        wav.fileSize      = decode(bytes, 4, 4);
        wav.headerType    = decode(bytes, 8, 4, false);
        wav.formatMarker  = decode(bytes, 12, 4, false);
        wav.formatLen     = decode(bytes, 16, 4);
        wav.formatType    = decode(bytes, 20, 2);
        wav.numOfChannels = decode(bytes, 22, 2);
        wav.sampleRate    = decode(bytes, 24, 4);
        wav.duration      = decode(bytes, 28, 4);
        wav.calc2         = decode(bytes, 32, 2);
        wav.bitsPerSample = decode(bytes, 34, 2);
        wav.dataHeader    = decode(bytes, 36, 4, false);
        wav.dataSize      = decode(bytes, 40, 4);
        qDebug() << "Duration:" << wav.duration / 1000.0 << "seconds";
        qDebug() << wav.duration / (double)wav.dataSize << "seconds";
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
            quint64 byte = (bytes[i] << (8 * counter));
            joined |= byte;
            counter = littleEndian ? (counter + 1) : (counter - 1);
        }
    }
    return joined;
}

bool AudioParser::inRange(int value, int min, int max)
{
    return value >= min && value <= max;
}
