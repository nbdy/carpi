//
// Created by insane on 02.06.19.
//

#include "PostgreSQLDB.h"

PostgreSQLDB::~PostgreSQLDB() {
    PQfinish(connection);
}

PostgreSQLDB::PostgreSQLDB() {
    uri = buildURI("localhost", 5432, "carpi");
    connection = connect(uri);
}

PostgreSQLDB::PostgreSQLDB(const std::string &uri) {
    this->uri = uri;
    connection = connect(uri);
}

PostgreSQLDB::PostgreSQLDB(const db::DatabaseConfiguration &cfg) {
    uri = buildURI(cfg.host, cfg.port, cfg.dbname); // todo username & password
    connection = connect(uri);
}

PostgreSQLDB::PostgreSQLDB(const std::string &host, int port, const std::string &database) {
    uri = buildURI(host, port, database);
    connection = connect(uri);
}

std::string PostgreSQLDB::buildURI(const std::string &host, int port, const std::string &database) {
    return "postgresql://" + database + "?host=" + host + "&port=" + std::to_string(port);
}

PGconn* PostgreSQLDB::connect(const std::string &uri) {
    return PQconnectdb(uri.c_str());
}