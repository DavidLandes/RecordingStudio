#pragma once

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QDebug>
#include "Globals.hpp"

class AudioDevice : public QObject
{
    Q_OBJECT
public:
    explicit AudioDevice(QObject *parent = nullptr);
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QAudioDeviceInfo info READ info WRITE setInfo NOTIFY infoChanged)
    Q_PROPERTY(QAudioInput* input READ input WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(QAudioFormat format READ format WRITE setFormat NOTIFY formatChanged)

    void initialize(QAudioDeviceInfo info);
    bool isReady();

    QAudioDeviceInfo info() const;
    void setInfo(QAudioDeviceInfo newInfo);

    QAudioInput* input() const;
    void setInput(QAudioInput* newInput);

    QString name() const;

    QAudioFormat format() const;
    void setFormat(QAudioFormat format);

signals:
    void infoChanged();
    void inputChanged();
    void nameChanged();

    void formatChanged();

private:
    void setName(QString microphoneName);
    QAudioDeviceInfo m_info;
    QAudioInput* m_input;
    QString m_name;
    QAudioFormat m_format;
};

