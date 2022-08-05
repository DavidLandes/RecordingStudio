#include "Track.hpp"

Track::Track(QString filePath, QObject *parent) : QObject(parent)
  , m_filePath(filePath)
  , m_offsetMs(0)
{

}

QString Track::filePath() const
{
    return m_filePath;
}

void Track::filePath(QString fileName)
{
    if (m_filePath != fileName)
    {
        m_filePath = fileName;
        emit filePathChanged(m_filePath);
    }
}

int Track::offsetMs() const
{
    return m_offsetMs;
}

void Track::setOffsetMs(int offsetMs)
{
    if (m_offsetMs != offsetMs)
    {
        m_offsetMs = offsetMs;
        emit offsetMsChanged(m_offsetMs);
    }
}
