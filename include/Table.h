#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <variant>
#include <unordered_map>

#include "ColumnMeta.h"

namespace db {
class Table {
private:
    uint64_t nextIndex;
    std::vector<ColumnMeta> columns;
    std::unordered_map<uint64_t, std::vector<value>> data;
public:
    void insert_query(std::vector<value> row);
    void delete_query();
    void select_query();
};
}
