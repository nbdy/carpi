#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <osmscout/OSMScoutQt.h>

#include <disqt/disqt.h>

#include "libs/Utils/Utils.h"
#include "libs/Settings/Settings.h"

// todo check for redis service with libsystemd-qt and start it if necessary
// todo handle segfault when redis is not running and client tried to connect

QJsonDocument loadConfig(const QString& fn){
    qDebug() << "loading configuration:" << fn;
    QFile f(fn);
    if(!f.exists()) return QJsonDocument();
    QString data;
    if(f.open(QIODevice::ReadOnly)) data = f.readAll();
    qDebug() << "configuration file exists and has been loaded";
    return QJsonDocument::fromJson(data.toUtf8());
}

bool writeConfig(const QString& fn, const QJsonDocument &doc){
    bool r = true;
    QFile f(fn);
    if(f.exists()) r = false;
    if(f.open(QIODevice::WriteOnly)) f.write(doc.toJson());
    qDebug() << "writing default config to '" << fn << "' was " << (!r ? "un" : "") << "successful";
    return r;
}

template<typename R> void setValue(QCommandLineParser &p, QCommandLineOption &opt, const QString& key, QJsonObject &o, R defaultValue){
    if(p.isSet(opt)) o.insert(key, p.value(opt));
    else o.insert(key, defaultValue);
}

QJsonDocument getDefaultConfig(){
    QJsonDocument r;
    QJsonObject o;
    o["maps"] = "/var/lib/carpi/maps/";
    o["style"] = "Material";
    o["stylesheet"] = "/usr/local/share/stylesheets/standard.oss";
    o["stylesheet-directory"] = "/usr/local/share/stylesheets/";
    o["cache-directory"] = "/var/lib/carpi/cache/";
    r.setObject(o);
    return r;
}


QJsonDocument parseArguments(QGuiApplication &app){
    QCommandLineParser clip;
    clip.setApplicationDescription("carpi");
    clip.addHelpOption();
    clip.addVersionOption();

    QCommandLineOption optionWriteConfig("write-config", QCoreApplication::translate("main", "write the default configuration to the specified path"), "config");
    QCommandLineOption optionConfig(QStringList() << "c" <<"config", QCoreApplication::translate("main", "json configuration file (overrides cli parameters)"), "config");
    QCommandLineOption optionMaps(QStringList() << "m" << "maps", QCoreApplication::translate("main", "folder to maps generated by libosmscout's Import tool"), "maps");
    QCommandLineOption optionStyle(QStringList() << "s" << "style", QCoreApplication::translate("main", "application style"), "style");
    QCommandLineOption optionStylesheet("stylesheet", QCoreApplication::translate("main", "stylesheet for map"), "stylesheet");
    QCommandLineOption optionStylesheetDirectory("stylesheet-directory", QCoreApplication::translate("main", "folder with osm stylesheets"), "stylesheet-directory");
    QCommandLineOption optionCacheDirectory("cache-directory", QCoreApplication::translate("main", "caching directory"), "caching-directory");

    clip.addOptions({
        optionWriteConfig, optionConfig, optionMaps, optionStyle, optionStylesheet, optionStylesheetDirectory, optionCacheDirectory
    });

    clip.process(app);

    if(clip.isSet(optionWriteConfig)) writeConfig(clip.value(optionWriteConfig), getDefaultConfig());

    QJsonDocument cfg;
    if(clip.isSet(optionConfig)) cfg = loadConfig(clip.value(optionConfig));
    else {
        qDebug() << "no config specified, using the default one";
        QJsonObject o;

        setValue(clip, optionMaps, "maps", o, "/media/data/map/osmscout");
        setValue(clip, optionStyle, "style", o, "Material");
        setValue(clip, optionStylesheet, "stylesheet", o, "/usr/local/share/stylesheets/standard.oss");
        setValue(clip, optionStylesheetDirectory, "stylesheet-directory", o, "/usr/share/local/stylesheets/");
        setValue(clip, optionCacheDirectory, "cache-directory", o, "/var/lib/carpi/cache");

        cfg.setObject(o);
    }

    return cfg;
}

bool checkConfiguration(const QJsonDocument& doc){
    qDebug() << doc.toJson();
    bool ok = true;
    qDebug() << "checking the configuration";
    if(!doc["maps"].toString().startsWith("/")) {
        qDebug() << "Error:" << doc["maps"].toString();
        qDebug() << "\tThe path to the maps folder must be absolute";
        ok = false;
    }
    return ok;
}

int main(int argc, char **argv)
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    RedisQT::registerType();
    Utils::registerTypes();
    Settings::registerTypes();

    osmscout::OSMScoutQt::RegisterQmlTypes("io.eberlein.carpi.map", 1, 0);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("eberlein");
    QGuiApplication::setOrganizationDomain("eberlein.io");
    QGuiApplication::setApplicationName("carpi");

    QJsonDocument cfg = parseArguments(app);
    if(cfg.isEmpty()) {
        qDebug() << "no configuration provided. exiting.";
        exit(-1);
    }

    if(!checkConfiguration(cfg)) exit(-1);

    QQuickStyle::setStyle(cfg["style"].toString());

    bool si = osmscout::OSMScoutQt::NewInstance()
            .WithCacheLocation(cfg["cache-directory"].toString())
            .WithStyleSheetFile(cfg["stylesheet"].toString())
            .WithStyleSheetDirectory(cfg["stylesheet-directory"].toString())
            .WithMapLookupDirectories(QStringList() << cfg["maps"].toString())
            .Init();

    if (!si) return -1;

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
