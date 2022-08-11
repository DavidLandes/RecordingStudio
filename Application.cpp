#include "Application.hpp"

Application::Application(QObject *parent) : QObject(parent)
{
}

Application::~Application()
{
}

void Application::onKeyboardEvent(QString event)
{
//    qDebug() << "Key Pressed:" << event;
}
