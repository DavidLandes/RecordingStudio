#pragma once

#include <QDebug>
#include <QObject>
#include <QFile>
#include <QtEndian>
#include <QTextStream>
#include <stdint.h>

#pragma pack(push, 1)
struct WaveHeader
{
    uint32_t riff             : 32;
    uint32_t fileSize         : 32;
    uint32_t headerType       : 32;
    uint32_t formatMarker     : 32;
    uint32_t formatLen        : 32;
    uint16_t formatType       : 16;
    uint16_t numOfChannels    : 16;
    uint32_t sampleRate       : 32;
    uint32_t duration         : 32;
    uint16_t calc2            : 16;
    uint16_t bitsPerSample    : 16;
    uint32_t dataHeader       : 32;
    uint32_t dataSize         : 32;
};
#pragma pack(pop)

class AudioParser : public QObject
{
    Q_OBJECT
public:
    explicit AudioParser(QObject *parent = nullptr);

    WaveHeader parseWav(QString filePath);

signals:

private:
    quint64 decode(QByteArray bytes, int start, int length, bool isLittleEndian=true);
    bool inRange(int value, int min, int max);
};

