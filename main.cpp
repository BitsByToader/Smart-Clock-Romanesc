#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "smartclock.h"

int main(int argc, char *argv[]) {
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    SmartClock *smartClock = new SmartClock();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QScopedPointer<SmartClock> example(smartClock);
    qmlRegisterSingletonInstance("tudor.SmartClock", 1, 0, "SmartClock", example.get());

    engine.load(url);

    return app.exec();
}
