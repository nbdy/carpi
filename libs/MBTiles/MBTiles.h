//
// Created by insane on 27.02.19.
//

#ifndef CARPI_MBTILES_H
#define CARPI_MBTILES_H


#include <string>
#include <iostream>
#include <sqlite3.h>
#include "../../sqlite3pp/headeronly_src/sqlite3pp.h"

class TileSetInfo {
private:
    std::string name;
    std::string type;
    std::string version;
    std::string description;
    std::string format;
    std::string bounds;
public:
    TileSetInfo();

    std::string getName();
    void setName(const std::string& name);
};

class MBTiles {
private:
    sqlite3pp::database db;

public:
    explicit MBTiles(const std::string& filepath);
    ~MBTiles();

    bool tileSetExists();
    //TileSetInfo *tileSetInfo();
    std::string getFormat();

    void getTile(int zoomLevel,
                 int tileColumn,
                 int tileRow,
                 std::string& r);
};


#endif //CARPI_MBTILES_H
