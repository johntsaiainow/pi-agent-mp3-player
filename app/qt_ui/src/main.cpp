#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "playercontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    PlayerController playerController;

    // 將 C++ 播放控制器註冊為 QML 全域 Context Property
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
