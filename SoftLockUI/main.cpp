#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qcryptoadaptor.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QCrpytoAdaptor adaptor(&app);
//    adaptor.encryptFile("/home/user/SoftLockProject/SoftLockUI/test", "/home/user/SoftLockProject/SoftLockUI/test2", "01234567890123456789012345678901", "0123456789012345");
    adaptor.decryptFile("/home/user/SoftLockProject/SoftLockUI/test2", "/home/user/SoftLockProject/SoftLockUI/test3", "01234567890123456789012345678901", "0123456789012345");
    //    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

    return app.exec();
}
