#pragma once

#include <QDebug>
#include <QObject>
#include <QKeySequence>
#include <QShortcut>
#include <QKeyEvent>
#include <QEvent>

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = nullptr);
    ~Application();

public slots:
    Q_INVOKABLE void onKeyboardEvent(QString event);

signals:

private:

};

