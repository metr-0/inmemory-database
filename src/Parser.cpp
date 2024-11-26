#include <string>
#include <regex>
#include <sstream>

#include "../include/Parser.h"

using sregex_iterator = std::regex_iterator<std::string::const_iterator, char>;

const std::regex table_name_regex(R"(create\s+table\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\((.*)\))");
const std::regex column_definition_regex(R"(([a-zA-Z_][a-zA-Z0-9_]*)\s*:\s*(int32|bool|string\[\d+\]|bytes\[\d+\])\s*(=\s*([^\s,]+))?\s*(\{.*\})?)");
const std::regex attribute_regex(R"(\{([^}]+)\})");

db::ColumnType db::Parser::column_type(const std::string &raw, size_t &size) {
    std::regex string_regex(R"(string\[(\d+)\])");
    std::regex bytes_regex(R"(bytes\[(\d+)\])");
    std::regex int_regex(R"(int32)");
    std::regex bool_regex(R"(bool)");

    std::smatch match;

    if (std::regex_match(raw, match, string_regex)) {
        size = std::stoi(match[1].str());
        return ColumnType::STRING;
    }
    if (std::regex_match(raw, match, bytes_regex)) {
        size = std::stoi(match[1].str());
        return ColumnType::BYTES;
    }
    if (std::regex_match(raw, int_regex))
        return ColumnType::INT;
    if (std::regex_match(raw, bool_regex))
        return ColumnType::BOOL;

    throw std::exception("Invalid column type");
}

db::CreateTableStatement db::Parser::create_table_statement(const std::string &raw) {
    db::CreateTableStatement result;

    std::smatch match;
    if (std::regex_match(raw, match, table_name_regex)) {
        result.name = match[1];
        std::string columns_str = match[2];

        auto column_begin = sregex_iterator(columns_str.begin(), columns_str.end(), column_definition_regex);
        auto column_end = sregex_iterator();

        for (auto it = column_begin; it != column_end; ++it) {
            db::ColumnMeta column;

            column.name = (*it)[1];
            column.type = db::Parser::column_type((*it)[2], column.size);

            if ((*it)[4].matched) column.default_value = (*it)[4];

            std::string attributes_str = (*it)[5];
            if (std::regex_search(attributes_str, match, attribute_regex)) {
                std::string attributes_list = match[1].str();
                std::stringstream ss(attributes_list);
                std::string attr;

                while (std::getline(ss, attr, ',')) {
                    attr = std::regex_replace(attr, std::regex("^ +| +$"), "");
                    if (attr == "unique") {
                        column.unique = true;
                    } else if (attr == "autoincrement") {
                        column.autoincrement = true;
                    } else if (attr == "key") {
                        column.key = true;
                    } else {
                        throw std::exception("Invalid attribute");
                    }
                }
            }

            result.columns.push_back(column);
        }
    } else {
        throw std::invalid_argument("Invalid CREATE TABLE command");
    }

    return result;
}
