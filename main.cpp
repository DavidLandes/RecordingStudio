
#include <QQmlContext>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Application.hpp"
#include "AudioController.hpp"
#include "Palette.hpp"
#include "Player.hpp"
#include "Project.hpp"
#include "ProjectController.hpp"
#include "Recorder.hpp"
#include "Theme.hpp"
#include "Track.hpp"
#include "WavFile.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qDebug() << "Starting Recording Studio -" << VERSION;

    // Initialize.
    Application* application = new Application();
    Palette* colors = new Palette();
    AudioController* audio = new AudioController();
    ProjectController* projects = new ProjectController();

    // Register types.
    qmlRegisterUncreatableType<Palette>("com.studio.Theme", 1, 0, "Palette", "Cannot create an instance of type \"Palette\"");
    qmlRegisterUncreatableType<Theme>("com.studio.Theme", 1, 0, "Theme", "Cannot create an instance of type \"Theme\"");
    qmlRegisterUncreatableType<AudioController>("com.studio.Audio", 1, 0, "AudioController", "Cannot create an instance of type \"AudioController\"");
    qmlRegisterUncreatableType<Recorder>("com.studio.Audio", 1, 0, "Recorder", "Cannot create an instance of type \"Recorder\"");
    qmlRegisterUncreatableType<WavFile>("com.studio.Audio", 1, 0, "WavFile", "Cannot create an instance of type \"WavFile\"");
    qmlRegisterUncreatableType<Track>("com.studio.Audio", 1, 0, "Track", "Cannot create an instance of type \"Track\"");

    QQmlApplicationEngine engine;

    // Register properties.
    engine.rootContext()->setContextProperty("application", application);
    engine.rootContext()->setContextProperty("colors", colors);
    engine.rootContext()->setContextProperty("audio", audio);
    engine.rootContext()->setContextProperty("projects", projects);


    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
