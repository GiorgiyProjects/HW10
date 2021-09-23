#define BOOST_TEST_MODULE tests
#include "CommandInterpreter.h"

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( TestSuite )
    BOOST_AUTO_TEST_CASE(test1) {
        CommandInterpreter S;
        DataBase DB;
        std::string result;
        result = S.receive("INSERT A 0 lean", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT A 0 understand", DB) ;
        BOOST_CHECK(result == "Err duplicate key");
        result = S.receive("INSERT A 1 sweater", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT A 2 frank", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT A 3 violation", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT A 4 quality", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT A 5 precision", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT B 3 proposal", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT B 4 example", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT B 5 lake", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT B 6 flour", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT B 7 wonder", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INSERT B 8 selection", DB);
        BOOST_CHECK(result == "OK!");
        result = S.receive("INTERSECTION", DB);
        BOOST_CHECK(result == "3,violation,proposal,\n"
                              "4,quality,example,\n"
                              "5,precision,lake,\n");
        result = S.receive("SYMMETRIC_DIFFERENCE", DB);
        BOOST_CHECK(result == "0,lean,\n"
                              "1,sweater,\n"
                              "2,frank,\n"
                              "6,,flour,\n"
                              "7,,wonder,\n"
                              "8,,selection,\n");
        result = S.receive("TRUNCATE A", DB);
        BOOST_CHECK(result == "OK!");
    }
BOOST_AUTO_TEST_SUITE_END()