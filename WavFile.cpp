#include "WavFile.hpp"

WavFile::WavFile(QString filePath, QObject *parent)
    : AudioParser{parent}
    , m_filePath(filePath)
{
    m_metaData = parseWav(filePath);
    m_duration = m_metaData.dataSize / (double) m_metaData.byteRate;
}

double WavFile::duration() const
{
    return m_duration;
}

const QString &WavFile::filePath() const
{
    return m_filePath;
}

const WavHeader &WavFile::metaData() const
{
    return m_metaData;
}
