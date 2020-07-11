//
// Created by insane on 11.02.19.
//

#ifndef CARPI_NAVIGATION_H
#define CARPI_NAVIGATION_H


#include <string>
#include <cmath>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <mapnik/load_map.hpp>
#include <mapnik/map.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/rule.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/symbolizer.hpp>
#include <mapnik/text/placements/dummy.hpp>
#include <mapnik/text/text_properties.hpp>
#include <mapnik/text/formatting/text.hpp>
#include <mapnik/datasource_cache.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/agg_renderer.hpp>
#include <mapnik/expression.hpp>
#include <mapnik/color_factory.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/unicode.hpp>

#include "../Configuration/Configuration.h"
#include "../GPS/GPS.h"
#include "../mbtiles-cpp/MBTileReader/MBTileReader.h"

class TileCache {
public:
    ~TileCache();
    explicit TileCache(const nc::NavigationConfiguration &navigationConfiguration);
    std::string getTile(Position *p, int z, std::pair<int, int> res);

private:
    nc::NavigationConfiguration cfg;
    MBTileReader *mbTileReader;

    void _setupMapnik();
    void _setupMBTiles();
    std::string _renderMBTilesImage(Position *p, int z, int width, int height);
    std::string _renderMapnikImage(Position *p, int z, int width, int height);
    std::string _buildFileName(double x, double y, int z, int width, int height);

    void _startWatchDog();
    void _watchDog();
    bool runWatchDog = false;
    double cacheDirectorySizeLimit = 20; // gb
    unsigned int watchDogSleepTime = 2;
    std::thread watchDogThread;

    mapnik::Map map;
    std::vector<std::string> cachedImages;
    std::vector<int> tileResolution;
};

class Routing {
public:
    Routing();
    ~Routing();
};

class Navigation {
private:
    TileCache *cache;
    Position *lastPosition;

public:
    explicit Navigation(const nc::NavigationConfiguration& cfg);
    std::string getImage(Position* position, int zoom);
    std::string getImage(Position* position, int zoom, int width, int height);
    double get2DRotation(Position* position);

    static double get2DRotation(Position* np, Position* op);
    static double getDistanceKm(Position *p1, Position *p2);

    static int long2tilex(double lon, int z);
    static int lat2tiley(double lat, int z);
    static double tilex2long(int x, int z);
    static double tiley2lat(int y, int z);
};


#endif //CARPI_NAVIGATION_H
