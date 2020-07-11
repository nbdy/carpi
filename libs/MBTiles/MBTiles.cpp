//
// Created by insane on 27.02.19.
//

#include "MBTiles.h"


TileSetInfo::TileSetInfo() {

}

std::string TileSetInfo::getName() {return name;}

void TileSetInfo::setName(const std::string& name) {this->name = name;}


MBTiles::MBTiles(const std::string& filepath) {
    db = sqlite3pp::database(filepath.c_str());
    if (tileSetExists()) std::cout << "tileset for '" << filepath << "' seems to exist" << std::endl;
    // std::cout << "here" << std::endl;
    // tileSetInfo(); // todo fix
    // std::cout << "there" << std::endl;
}

MBTiles::~MBTiles() {

}

bool MBTiles::tileSetExists() {
    //sqlite3pp::query q1(db, "SELECT name, value FROM metadata LIMIT 1");
    // sqlite3pp::query q2(db, "SELECT zoom_level, tile_column, tile_row, tile_data FROM tiles LIMIT 1");
    // return (q1.column_count() > 0 && q2.column_count() > 0);
}

/*
TileSetInfo* MBTiles::tileSetInfo() {
    static std::vector<std::string> keys = {"name", "type", "version", "description", "format", "bounds"};
    static std::string query = "SELECT value FROM metadata WHERE name = ";
    std::vector<std::string> r;
    for(const std::string& key : keys){
        std::string val;
        std::string q1 = query + key;
        std::cout << q1 << std::endl;
        sqlite3pp::query q(db, q1.c_str());
        for(auto v : q){
            //v.getter() >> sqlite3pp::ignore >> val;
        }
    }
    return new TileSetInfo();
}
 */

// https://github.com/TimSC/mbtiles-cpp/blob/master/Source/MBTileReader.cpp
void MBTiles::getTile(int zoomLevel, int tileColumn, int tileRow, std::string& r) {
    r.clear();
    sqlite3pp::query qry(db, "SELECT tile_data FROM tiles WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?;");
    qry.bind(1, zoomLevel);
    qry.bind(2, tileColumn);
    qry.bind(3, tileRow);
    std::string tmp;
    for(auto v : qry){
        tmp.insert(0, (const char *) v.get<const void *>(0), v.column_bytes(0));
        break;
    }
    std::cout << r.size() << std::endl;
}

std::string MBTiles::getFormat() {
    sqlite3pp::query qry(db, "SELECT value FROM metadata WHERE name='format'");
    for(auto v : qry){
        return v.get<const char*>(0);
    }
    return "";
}