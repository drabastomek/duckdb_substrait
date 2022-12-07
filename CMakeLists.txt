cmake_minimum_required(VERSION 3.10)
project(duckdb_substrait)

set(CMAKE_CXX_STANDARD 17)

# find_package(Threads REQUIRED)
# find_package(Arrow REQUIRED)
# find_package(ArrowFlight REQUIRED)
# find_package(ArrowFlightSql REQUIRED)
# find_package(Protobuf REQUIRED)

# # find_package(SQLite3 REQUIRED)
# find_package(Boost COMPONENTS program_options REQUIRED)

# find duckDB
find_library(DUCKDB_LIB NAMES duckdb PATHS $ENV{CONDA_PREFIX}/lib/)
set(DUCKDB ${DUCKDB_LIB})

# set(ARROW_FLIGHT_SQL_SUBSTRAIT_DUCKDB_SERVER_SRCS
#     src/substrait_duckdb/substrait_duckdb_sql_info.cpp
#     src/substrait_duckdb/substrait_duckdb_statement.cpp
#     src/substrait_duckdb/substrait_duckdb_statement_batch_reader.cpp
#     src/substrait_duckdb/substrait_duckdb_server.cpp
# )

# set(ARROW_FLIGHT_DUCKDB_SQLITE_SERVER_SRCS
#     src/duckdb/duckdb_sql_info.cpp
#     src/duckdb/duckdb_statement.cpp
#     src/duckdb/duckdb_statement_batch_reader.cpp
#     src/duckdb/duckdb_server.cpp
# )

# set(SUBSTRAIT_SRCS 
#     src/substrait_duckdb/substrait/algebra.pb.cc
#     src/substrait_duckdb/substrait/capabilities.pb.cc
#     src/substrait_duckdb/substrait/function.pb.cc
#     src/substrait_duckdb/substrait/parameterized_types.pb.cc
#     src/substrait_duckdb/substrait/plan.pb.cc
#     src/substrait_duckdb/substrait/type_expressions.pb.cc
#     src/substrait_duckdb/substrait/type.pb.cc
#     src/substrait_duckdb/substrait/extensions/extensions.pb.cc
# )

add_executable(duckdb_substrait 
    main.cpp
    # ${ARROW_FLIGHT_SQL_SUBSTRAIT_DUCKDB_SERVER_SRCS}
    # ${ARROW_FLIGHT_DUCKDB_SQLITE_SERVER_SRCS}
    # ${SUBSTRAIT_SRCS}
)

# target_include_directories(flight_sql PRIVATE 
#     src/substrait_duckdb
#     # src/duckdb
# )
# target_include_directories(flight_sql PRIVATE src/duckdb)
target_link_libraries(duckdb_substrait PRIVATE 
		    #   arrow_shared
		    #   arrow_flight_shared
		    #   arrow_flight_sql_shared
            #   ${PROTOBUF_LIBRARY}
            #   Threads::Threads
              ${DUCKDB}
            #   ${Boost_LIBRARIES}
              )