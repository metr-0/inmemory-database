cmake_minimum_required(VERSION 3.16)
project(Database)

set(CMAKE_CXX_STANDARD 20)

add_library(Database src/Parser.cpp include/Parser.h include/ColumnMeta.h include/Table.h include/Database.h include/Result.h)
