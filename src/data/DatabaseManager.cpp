// DatabaseManager.cpp
#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& filename)
    : db(nullptr), dbName(filename) {}

DatabaseManager::~DatabaseManager() {
    close();
}

bool DatabaseManager::open() {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "❌ Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void DatabaseManager::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::setupTables() {
    const char* createGamesTable =
        "CREATE TABLE IF NOT EXISTS Games ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "player_white TEXT,"
        "player_black TEXT,"
        "result TEXT,"
        "start_time TEXT,"
        "end_time TEXT"
        ");";

    const char* createMovesTable =
        "CREATE TABLE IF NOT EXISTS Moves ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "game_id INTEGER,"
        "turn INTEGER,"
        "piece TEXT,"
        "color TEXT,"
        "from_square TEXT,"
        "to_square TEXT,"
        "timestamp TEXT,"
        "FOREIGN KEY(game_id) REFERENCES Games(id)"
        ");";

    char* errMsg = nullptr;

    if (sqlite3_exec(db, createGamesTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "❌ Error creating Games table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    if (sqlite3_exec(db, createMovesTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "❌ Error creating Moves table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    std::cout << "✅ Tables ensured in database." << std::endl;
    return true;
}