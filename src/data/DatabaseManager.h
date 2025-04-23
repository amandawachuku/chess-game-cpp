// DatabaseManager.h
#pragma once
#include <string>
#include <sqlite3.h>

class DatabaseManager {
private:
    sqlite3* db;
    std::string dbName;

public:
    DatabaseManager(const std::string& filename);
    ~DatabaseManager();

    bool open();
    void close();
    bool setupTables();
    bool logMove(int game_id, int turn, const std::string& piece, const std::string& color, const std::string& from, const std::string& to);
};
