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
    Q_PROPERTY(QAudioInput* audioInput READ audioInput WRITE setAudioInput NOTIFY audioInputChanged)

    void initialize(QAudioDeviceInfo info);
    bool isReady();

    QAudioDeviceInfo info() const;
    void setInfo(QAudioDeviceInfo newInfo);

    QAudioInput* audioInput() const;
    void setAudioInput(QAudioInput* newAudioInput);

    QString name() const;

signals:
    void infoChanged();
    void audioInputChanged();
    void nameChanged();

private:
    void setName(QString microphoneName);
    QAudioDeviceInfo m_info;
    QAudioInput* m_audioInput;
    QString m_name;
};

