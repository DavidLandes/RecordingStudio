#pragma once

#include <QObject>

class AudioData : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QByteArray hex READ hex WRITE setHex NOTIFY hexChanged)
    explicit AudioData(QObject *parent = nullptr);

    QByteArray hex() const;
    void setHex(QByteArray newHex);

signals:

    void hexChanged();
private:
    QByteArray m_hex;
};

