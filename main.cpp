#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <osmscout/OSMScoutQt.h>

#include <disqt/disqt.h>

#include "libs/IsFile/IsFile.h"
#include "libs/CPUTemperature/CPUTemperature.h"
#include "libs/AsyncSettings/AsyncSettings.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    RedisQT::registerQmlType();
    qmlRegisterType<IsFile>("utils", 1, 0, "IsFile");
    qmlRegisterType<CPUTemperature>("utils", 1, 0, "CPUTemperature");
    qmlRegisterType<AsyncSettings>("utils", 1, 0, "AsyncSettings");

    osmscout::OSMScoutQt::RegisterQmlTypes("io.eberlein.carpi.map");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    QGuiApplication::setOrganizationName("eberlein");
    QGuiApplication::setOrganizationDomain("eberlein.io");
    QGuiApplication::setApplicationName("carpi");

    bool si = osmscout::OSMScoutQt::NewInstance()
            .WithStyleSheetFile("/usr/local/share/stylesheets/standard.oss")
            .WithStyleSheetDirectory("/usr/share/local/stylesheets/")
            .WithMapLookupDirectories(QStringList() << "/home/insane/maps/bayern-latest/")
            .Init();

    if(!si) return -1;

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/qml/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    int rc = QGuiApplication::exec();
    osmscout::OSMScoutQt::FreeInstance();
    return rc;
}
