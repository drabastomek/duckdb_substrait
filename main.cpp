#include <iostream>
#include <duckdb.hpp>

int main() {
    auto db = std::make_unique<duckdb::DuckDB>("TPC-H-small_new.duckdb");
    auto conn = std::make_unique<duckdb::Connection>(*db);
    conn->Query("INSTALL substrait; LOAD substrait;"); // this doesn't really do anything...

    // check that the connection works
    auto result = conn->Query("SHOW TABLES");
    std::cout << result->ToString() << std::endl;

    std::string str_new = "\\x12\\x07\\x1A\\x05\\x10\\x01\\x1A\\x01-\\x1A\\xFE\\x03\\x12\\xFB\\x03\\x0A\\xE5\\x03:\\xE2\\x03\\x12\\xC9\\x03\\x1A\\xC6\\x03\\x12\\xC1\\x03*\\xBE\\x03\\x12\\x8B\\x03:\\x88\\x03\\x12\\xE3\\x02\\x0A\\xE0\\x02\\x12\\xBF\\x02\\x0A\\x0AL_ORDERKEY\\x0A\\x09L_PARTKEY\\x0A\\x09L_SUPPKEY\\x0A\\x0CL_LINENUMBER\\x0A\\x0AL_QUANTITY\\x0A\\x0FL_EXTENDEDPRICE\\x0A\\x0AL_DISCOUNT\\x0A\\x05L_TAX\\x0A\\x0CL_RETURNFLAG\\x0A\\x0CL_LINESTATUS\\x0A\\x0AL_SHIPDATE\\x0A\\x0CL_COMMITDATE\\x0A\\x0DL_RECEIPTDATE\\x0A\\x0EL_SHIPINSTRUCT\\x0A\\x0AL_SHIPMODE\\x0A\\x09L_COMMENT\\x12q\\x0A\\x04*\\x02\\x10\\x01\\x0A\\x04*\\x02\\x10\\x01\\x0A\\x04*\\x02\\x10\\x01\\x0A\\x04*\\x02\\x10\\x01\\x0A\\x04*\\x02\\x10\\x01\\x0A\\x04*\\x02\\x10\\x01\\x0A\\x04*\\x02\\x10\\x01\\x0A\\x04*\\x02\\x10\\x01\\x0A\\x07\\xB2\\x01\\x04\\x08\\x01\\x18\\x01\\x0A\\x07\\xB2\\x01\\x04\\x08\\x01\\x18\\x01\\x0A\\x04r\\x02\\x10\\x01\\x0A\\x04r\\x02\\x10\\x01\\x0A\\x04r\\x02\\x10\\x01\\x0A\\x07\\xB2\\x01\\x04\\x08\\x11\\x18\\x01\\x0A\\x07\\xB2\\x01\\x04\\x08\\x07\\x18\\x01\\x0A\\x07\\xB2\\x01\\x04\\x08+\\x18\\x01\\x18\\x02\\x22\\x10\\x0A\\x0C\\x0A\\x02\\x08\\x07\\x0A\\x02\\x08\\x06\\x0A\\x02\\x08\\x01\\x10\\x01:\\x0A\\x0A\\x08lineitem\\x1A\\x08\\x12\\x06\\x0A\\x02\\x12\\x00\\x22\\x00\\x1A\\x0A\\x12\\x08\\x0A\\x04\\x12\\x02\\x08\\x01\\x22\\x00\\x1A\\x0A\\x12\\x08\\x0A\\x04\\x12\\x02\\x08\\x02\\x22\\x00\\x1A.\\x0A*Z(\\x0A\\x04*\\x02\\x10\\x01\\x12 \\x1A\\x1E\\x08\\x01\\x1A\\x04*\\x02\\x10\\x01\\x22\\x0C\\x1A\\x0A\\x12\\x08\\x0A\\x04\\x12\\x02\\x08\\x02\\x22\\x00\\x22\\x06\\x1A\\x04\\x0A\\x02(\\x01\\x10\\x01 \\x0A\\x1A\\x08\\x12\\x06\\x0A\\x02\\x12\\x00\\x22\\x00\\x1A\\x0A\\x12\\x08\\x0A\\x04\\x12\\x02\\x08\\x01\\x22\\x00\\x12\\x05L_TAX\\x12\\x0AL_DISCOUNT";
    // this throws
    // auto prepare = conn->Prepare("CALL from_substrait(\'" + str_new + "\'::BLOB);");
    // auto result_substrait  = prepare->Execute(8);

    // this returns 0 rows
    auto result_substrait  = conn->Query("INSTALL substrait; LOAD substrait; CALL from_substrait(\'" + str_new + "\'::BLOB);");
    std::cout << result_substrait->ToString() << std::endl;

    // let's try getting the blob directly
    auto blob = conn->Query("INSTALL substrait; LOAD substrait; CALL get_substrait(\"SELECT * FROM lineitem LIMIT 10\");");
    std::cout << blob->ToString() << std::endl; // this does not work either...

    // SQL query
    // this works as intended
    auto prepare = conn->Query("SELECT * FROM lineitem LIMIT 10");
    std::cout << prepare->ToString() << std::endl;

    return 0;
}