#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "playercontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    PlayerController playerController;

    // 關鍵！必須在 load 之前注入 context property "player"
    engine.rootContext()->setContextProperty("player", &playerController);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
