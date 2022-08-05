#pragma once

#include <QObject>

class Theme : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(int foreground READ foreground WRITE setForeground NOTIFY foregroundChanged)
    Q_PROPERTY(int accent READ accent WRITE setAccent NOTIFY accentChanged)

    explicit Theme(QObject *parent = nullptr);
    Theme(int background, int foreground, int accent, QObject *parent = nullptr);

    int background() const;
    int foreground() const;
    int accent() const;

public slots:
    void setBackground(int background);
    void setForeground(int foreground);
    void setAccent(int accent);

signals:
    void backgroundChanged(int background);
    void foregroundChanged(int foreground);
    void accentChanged(int accent);

private:
    int m_background;
    int m_foreground;
    int m_accent;
};

