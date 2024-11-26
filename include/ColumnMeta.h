#pragma once

#include <string>
#include <variant>
#include <vector>
#include <cstdint>

namespace db {
typedef std::variant<int32_t, bool, std::string, std::vector<uint8_t>> value;
enum ColumnType {INT, BOOL, STRING, BYTES};

struct ColumnMeta {
    std::string name;
    ColumnType type;
    size_t size;
    value default_value;

    bool unique;
    bool autoincrement;
    bool key;
};
}
