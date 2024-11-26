#pragma once

#include <string>
#include <unordered_map>

#include "Result.h"
#include "Table.h"

namespace db {
class Database {
private:
    std::unordered_map<std::string, db::Table> tables;
public:
    void load(std::string filename);
    void save(std::string filename) const;

    db::Result execute(std::string query);
};
}
