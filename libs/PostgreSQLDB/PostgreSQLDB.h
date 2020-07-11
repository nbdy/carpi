//
// Created by insane on 02.06.19.
//

#ifndef CARPI_POSTGRESQLDB_H
#define CARPI_POSTGRESQLDB_H

#include <string>
#include <postgresql/libpq-fe.h>
#include "../Device/Device.h"
#include "../Configuration/Configuration.h"

class PostgreSQLDB {
public:
    ~PostgreSQLDB();
    PostgreSQLDB();
    explicit PostgreSQLDB(const db::DatabaseConfiguration& cfg);
    explicit PostgreSQLDB(const std::string& uri);
    PostgreSQLDB(const std::string& host, int port, const std::string& database);

    static std::string buildURI(const std::string& host, int port, const std::string& database);
    static PGconn *connect(const std::string& uri);

    bool insertDevice(Device* device);
    bool insertPosition(Position* position);

private:
    std::string uri;
    PGconn *connection;
};


#endif //CARPI_POSTGRESQLDB_H
