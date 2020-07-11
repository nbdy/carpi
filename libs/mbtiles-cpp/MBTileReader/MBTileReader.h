//
// Created by insane on 02.05.19.
//

#ifndef MBTILESCPP_MBTILEREADER_H
#define MBTILESCPP_MBTILEREADER_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cmath>
#include <sqlite3.h>
#include "../VectorTile/VectorTile.h"

typedef std::vector<std::vector<unsigned int> > TileInfoRows;

class MBTileReader {
public:
    explicit MBTileReader(const char *filename);

    virtual ~MBTileReader();

    std::string GetMetadata(const char *metaField);

    void GetMetadataFields(std::vector<std::string> &fieldNamesOut);

    void ListTiles(TileInfoRows &tileInfoRowsOut);

    void GetTile(unsigned int zoomLevel,
                 unsigned int tileColumn,
                 unsigned int tileRow,
                 std::string &blobOut);

protected:
    sqlite3 *db;
    std::map<std::string, std::string> metadata;

    static int MetadataCallbackStatic(void *obj, int argc, char **argv, char **azColName);

    int MetadataCallback(int argc, char **argv, char **azColName);

    static int ListTilesCallbackStatic(void *rawPtr, int argc, char **argv, char **azColName);
};


#endif //MBTILESCPP_MBTILEREADER_H
