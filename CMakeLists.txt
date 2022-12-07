cmake_minimum_required(VERSION 3.10)
project(duckdb_substrait)

set(CMAKE_CXX_STANDARD 17)

# find duckDB
find_library(DUCKDB_LIB NAMES duckdb PATHS $ENV{CONDA_PREFIX}/lib/)
set(DUCKDB ${DUCKDB_LIB})

add_executable(duckdb_substrait 
    main.cpp
)

target_link_libraries(duckdb_substrait PRIVATE 
              ${DUCKDB}
              )