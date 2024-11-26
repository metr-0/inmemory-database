#pragma once

#include <vector>

#include "ColumnMeta.h"

namespace db {
struct CreateTableStatement {
    std::string name;
    std::vector<db::ColumnMeta> columns;
};

struct InsertValue {
    std::string column_name;
    std::string value;
};
struct InsertStatement {
    std::string table_name;
    db::InsertValue values;
};
}
