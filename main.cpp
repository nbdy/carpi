#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <osmscout/OSMScoutQt.h>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    osmscout::OSMScoutQt::RegisterQmlTypes();

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
