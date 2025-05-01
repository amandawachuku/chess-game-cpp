
#include <sqlite3.h>
#include <iostream>

int main() {
    std::cout << "Checking SQLite setup...\n";

    sqlite3* db;
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {
        std::cerr << "❌ Failed to open DB: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    std::cout << "✅ SQLite is working! Database opened successfully.\n";

    sqlite3_close(db);

    std::cout << "Press Enter to exit...";
    std::cin.get(); // 👈 keeps window open if you're double-clicking exe
    return 0;
}


