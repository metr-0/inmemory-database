#pragma once

#include <string>

#include "ColumnMeta.h"
#include "Statements.h"

namespace db {
enum Command {CREATE_TABLE, INSERT};

class Parser {
public:
    static db::ColumnType column_type(const std::string &raw, size_t &size);
    static db::Command command(const std::string &raw);

    static db::CreateTableStatement create_table_statement(const std::string &raw);
    static db::InsertStatement insert_statement(const std::string &raw);
};
}
