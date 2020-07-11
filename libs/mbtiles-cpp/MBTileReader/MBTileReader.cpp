//
// Created by insane on 02.05.19.
//

#include "MBTileReader.h"

MBTileReader::MBTileReader(const char *filename) {
    this->db = nullptr;

    int status = sqlite3_open(filename, &this->db);
    if (status) {
        sqlite3_close(this->db);
        std::cout << "could not open database" << std::endl;
    }

    char *zErrMsg = nullptr;
    status = sqlite3_exec(this->db, "SELECT * FROM metadata;", this->MetadataCallbackStatic, this, &zErrMsg);
    if (status != SQLITE_OK) {
        std::string err("SQL error: ");
        err += zErrMsg;
        sqlite3_free(zErrMsg);
        std::cout << err << std::endl;
    }
}

MBTileReader::~MBTileReader() {
    sqlite3_close(this->db);
}

int MBTileReader::MetadataCallbackStatic(void *obj, int argc, char **argv, char **azColName) {
    return ((MBTileReader *) obj)->MetadataCallback(argc, argv, azColName);
}

int MBTileReader::MetadataCallback(int argc, char **argv, char **azColName) {
    std::string name, value;
    for (int i = 0; i < argc; i++) {
        if (strncmp(azColName[i], "name", 5) == 0)
            name = (argv[i] ? argv[i] : "NULL");
        if (strncmp(azColName[i], "value", 6) == 0)
            value = (argv[i] ? argv[i] : "NULL");
    }
    if (name.size() > 0)
        this->metadata[name] = value;
    return 0;
}

std::string MBTileReader::GetMetadata(const char *metaField) {
    return metadata[metaField];
}

void MBTileReader::GetMetadataFields(std::vector<std::string> &fieldNamesOut) {
    fieldNamesOut.clear();
    for (std::map<std::string, std::string>::iterator it = metadata.begin(); it != metadata.end(); it++)
        fieldNamesOut.push_back(it->first);
}

int MBTileReader::ListTilesCallbackStatic(void *rawPtr, int argc, char **argv, char **azColName) {
    TileInfoRows *tileInfoRows = (TileInfoRows *) rawPtr;

    if (argc != 3)std::cout << "Database returned unexpected number of columns" << std::endl;
    std::vector<unsigned int> row;
    if (argv[0] == nullptr || argv[1] == nullptr || argv[2] == nullptr)
        std::cout << "Valid tile descriptor" << std::endl;
    row.push_back(atoi(argv[0])); //This is a bit silly since the data is stored as integers in the database!
    row.push_back(atoi(argv[1]));
    row.push_back(atoi(argv[2]));
    tileInfoRows->push_back(row);
    return 0;
}

void MBTileReader::ListTiles(TileInfoRows &tileInfoRowsOut) {
    char *zErrMsg = nullptr;
    int status = sqlite3_exec(this->db, "SELECT zoom_level, tile_column, tile_row FROM tiles;",
                              this->ListTilesCallbackStatic, &tileInfoRowsOut, &zErrMsg);
    if (status != SQLITE_OK) {
        std::string err("SQL error: ");
        err += zErrMsg;
        sqlite3_free(zErrMsg);
        std::cout << err << std::endl;
    }
}

void MBTileReader::GetTile(unsigned int zoomLevel,
                           unsigned int tileColumn,
                           unsigned int tileRow,
                           std::string &blobOut) {
    sqlite3_stmt *stmt = NULL;
    blobOut.clear();
    int status = sqlite3_prepare(this->db,
                                 "SELECT tile_data FROM tiles WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?;",  // stmt
                                 -1, // If than zero, then stmt is read up to the first nul terminator
                                 &stmt,
                                 0  // Pointer to unused portion of stmt
    );
    if (status != SQLITE_OK)std::cout << "Could not prepare statement" << std::endl;

    status = sqlite3_bind_int(stmt, 1, zoomLevel);
    if (status != SQLITE_OK) std::cout << "Could not bind value to statement" << std::endl;
    status = sqlite3_bind_int(stmt, 2, tileColumn);
    if (status != SQLITE_OK) std::cout << "Could not bind value to statement" << std::endl;
    status = sqlite3_bind_int(stmt, 3, tileRow);
    if (status != SQLITE_OK) std::cout << "Could not bind value to statement" << std::endl;

    status = SQLITE_ROW;
    bool firstRow = true;
    while (status == SQLITE_ROW) {
        status = sqlite3_step(stmt);
        if (firstRow && status == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            std::cout << "Tile not found" << std::endl;
            return;
        }

        if (status == SQLITE_ROW) {
            int numBytes = sqlite3_column_bytes(stmt, 0);
            const void *blobRaw = sqlite3_column_blob(stmt, 0);
            blobOut.insert(0, (const char *) blobRaw, numBytes); //Copy result to output
            sqlite3_finalize(stmt);
            return;
        }
        firstRow = false;
    }

    sqlite3_finalize(stmt);
    std::cout << "Error retrieving tile from database" << std::endl;
}

