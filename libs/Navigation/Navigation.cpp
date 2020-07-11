//
// Created by insane on 11.02.19.
//

#include <iostream>
#include <mapnik/projection.hpp>
#include <raylib.h>
#include "Navigation.h"

inline double degreeToRadian(double angle) {
    return M_PI * angle / 180.0;
}

// todo
// https://github.com/Project-OSRM/osrm-backend/blob/master/example/example.cpp

TileCache::TileCache(const nc::NavigationConfiguration &navigationConfiguration) {
    this->cfg = navigationConfiguration;
    tileResolution = navigationConfiguration.tileResolution;
    if(navigationConfiguration.cacheDirectory.empty()) cfg.cacheDirectory = "/var/lib/carpi/map/cache";
    if(!Utils::isDirectory(cfg.cacheDirectory)) Utils::createDirectory(cfg.cacheDirectory);
    if(navigationConfiguration.provider == "mbtiles"){
        _setupMBTiles();
    } else if(navigationConfiguration.provider == "mapnik"){
        if(!Utils::isFile(navigationConfiguration.infile)) cfg.infile = "/etc/carpi/mapnik.xml";
        _setupMapnik();
    } else {
        std::cout << "provider '" << navigationConfiguration.provider << "' is not known" << std::endl;
    }
    if(!Utils::endsWith(cfg.cacheDirectory, "/")) cfg.cacheDirectory += "/";
    //_startWatchDog();
}

void TileCache::_setupMBTiles() {
    mbTileReader = new MBTileReader(cfg.infile.c_str());
    std::cout << "using mbtiles provider" << std::endl;
    std::cout << "loading file: " << cfg.infile << std::endl;
    std::cout << "mbtiles information:\n\tname: " << mbTileReader->GetMetadata("name") << std::endl;
    std::cout << "\ttype: " << mbTileReader->GetMetadata("type") << std::endl;
    std::cout << "\tversion: " << mbTileReader->GetMetadata("version") << std::endl;
    std::cout << "\tdescription: " << mbTileReader->GetMetadata("description") << std::endl;
    std::cout << "\tformat: " << mbTileReader->GetMetadata("format") << std::endl;
    std::cout << "\tbounds: " << mbTileReader->GetMetadata("bounds") << std::endl;
}

std::string TileCache::getTile(Position* p, int z, std::pair<int, int> res) {
    std::string outFileName = _buildFileName(p->getLongitude(), p->getLatitude(), z, res.first, res.second);
    if(Utils::contains(cachedImages, outFileName)) return outFileName;
    if(cfg.provider == "mapnik"){
        return _renderMapnikImage(p, z, res.first, res.second);
    } else if(cfg.provider == "mbtiles"){
        return _renderMBTilesImage(p, z, res.first, res.second);
    } else {
        return "";
    }
}

void TileCache::_startWatchDog() {
    runWatchDog = true;
    watchDogThread = std::thread([&]{_watchDog();});
}

std::string TileCache::_renderMBTilesImage(Position *p, int z, int width, int height) {
    // todo: read pbf tile and visualize with vector gfx lib
}

std::string TileCache::_renderMapnikImage(Position *p, int z, int width, int height) {
    std::string rv = _buildFileName(p->getLongitude(), p->getLatitude(), z, width, height);
    std::cout << rv << std::endl;
    mapnik::image_rgba8 image(width, height);
    double x = p->getLongitude();
    double y = p->getLatitude();
    double _z = z;
    mapnik::projection llp = mapnik::projection("+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs");
    mapnik::projection mercp = mapnik::projection("+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +no_defs +over");
    mapnik::proj_transform transform(llp, mercp);
    double dx = ((20037508.34*2*(width/2)))/(256*(pow(2.0, z)));
    transform.forward(x, y, _z);
    double minx = x - dx;
    double maxx = x + dx;
    map.set_aspect_fix_mode(mapnik::Map::aspect_fix_mode::ADJUST_BBOX_HEIGHT);
    mapnik::box2d<double> bounds = mapnik::box2d<double>(minx, y - 10, maxx, y + 10);
    map.zoom_to_box(bounds);
    mapnik::agg_renderer<mapnik::image_rgba8> renderer(map, image);
    renderer.apply();
    mapnik::save_to_file(image, rv, "png8");
    cachedImages.emplace_back(rv);
    return rv;
}

std::string TileCache::_buildFileName(double x, double y, int z, int width, int height) {
    x = floor(x * 1000) / 1000; // three digits past decimal should be enough accuracy
    y = floor(y * 1000) / 1000; // cache folder should not fill up too much (5 * 5 * 10 * 3 * w * h) tiles; 255*255: 48768750 @ 200kb/img: 9753 gb
    std::string outFileName = cfg.cacheDirectory + "x" + std::to_string(x) + "y" + std::to_string(y) + "z" + std::to_string(z) + "w" + std::to_string(width) + "h" + std::to_string(height) + ".png";
    return outFileName;
}

void TileCache::_setupMapnik() {
    std::cout << "using mapnik provider" << std::endl;
    std::cout << "with stylesheet: " << cfg.infile << std::endl;
    mapnik::datasource_cache::instance().register_datasource("/usr/lib/mapnik/3.0/input/postgis.input"); // todo make variable or find automatically via mapnik-config

    map = mapnik::Map(580, 586); // todo set via config
    map.set_srs("+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0.0 +k=1.0 +units=m +nadgrids=@null +wktext +no_defs +over");
    mapnik::load_map(map, cfg.infile);
    // _buildStyle();
}



double Navigation::get2DRotation(Position *np, Position *op) {
    double x = np->getLongitude() - op->getLongitude();
    double y = np->getLatitude() - op->getLatitude();
    double r;
    if(x > 0) r = (PI * 0.5) - atan(y / x);
    else if (x < 0) r = (PI * 1.5) - atan(y / x);
    else if(y > 0) r = 0;
    else if(y < 0) r = PI;
    else r = 42;
    return r;
}

double Navigation::get2DRotation(Position* position) {
    return get2DRotation(position, lastPosition);
}

void TileCache::_watchDog() {
    int index = 0;
    while(runWatchDog){
        /*
         * * todo
        double directorySize = Utils::getDirectorySize(cacheDirectory);
        while (directorySize >= cacheDirectorySizeLimit && !cachedImages.empty()) {
            std::string cmd = "rm " + cachedImages[index];
            cachedImages.erase(cachedImages.begin() + index);
            system(cmd.c_str());
            index++;
            directorySize = Utils::getDirectorySize(cacheDirectory);
        }
        */
        sleep(watchDogSleepTime);
    }
}

TileCache::~TileCache() {
    runWatchDog = false;
}

Routing::Routing() {
    // todo osrm stuff
}

Navigation::Navigation(const nc::NavigationConfiguration& cfg) {
    this->cache = new TileCache(cfg);
    this->lastPosition = new Position();
}

std::string Navigation::getImage(Position *position, int zoom) {
    return cache->getTile(position, zoom, {600, 600});
}

double Navigation::getDistanceKm(Position *p1, Position *p2) {
    static double earthRadiusKm = 6371.8; // todo set via config so can be used on other planets
    double latRad1 = degreeToRadian(p1->getLatitude());
    double latRad2 = degreeToRadian(p2->getLatitude());
    double lngRad1 = degreeToRadian(p1->getLongitude());
    double lngRad2 = degreeToRadian(p2->getLongitude());
    double diffLa = latRad2 - latRad1;
    double doffLo = lngRad2 - lngRad1;
    double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
    return 2 * earthRadiusKm * computation;
}

std::string Navigation::getImage(Position *position, int zoom, int width, int height) {
    return cache->getTile(position, zoom, {width, height});
    // todo stitch image from
}

int Navigation::long2tilex(double lon, int z) {return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));}

int Navigation::lat2tiley(double lat, int z) {return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z)));}

double Navigation::tilex2long(int x, int z) {return x / pow(2.0, z) * 360.0 - 180;}

double Navigation::tiley2lat(int y, int z) {
    double n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
    return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}