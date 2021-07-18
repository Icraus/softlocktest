#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "fileobject.h"
#include "qcryptoadaptor.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication::addLibraryPath("./");
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QCrpytoAdaptor adaptor(&app);
    QQmlApplicationEngine engine;
    app.setOrganizationName("SoftLock");
    app.setOrganizationDomain("SoftLock.com");
    app.setApplicationName("SoftLock");

    qmlRegisterType<FileObject>("com.softlock", 1, 0, "FileObject");
    engine.rootContext()->setContextProperty("crypto", &adaptor);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                      &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}
