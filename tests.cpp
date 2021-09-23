#define BOOST_TEST_MODULE tests
#include "async_server.h"

#include <boost/test/included/unit_test.hpp>
namespace ba = boost::asio;


BOOST_AUTO_TEST_SUITE( TestSuite )

    struct cout_redirect {
        cout_redirect( std::streambuf * new_buffer )
                : old( std::cout.rdbuf( new_buffer ) )
        { }

        ~cout_redirect( ) {
            std::cout.rdbuf( old );
        }

    private:
        std::streambuf * old;
    };

    void Input1()
    {
        boost::asio::io_service io_service1;
        ba::ip::tcp::endpoint ep(ba::ip::address::from_string("127.0.0.1"), 8031);
        ba::ip::tcp::socket sock(io_service1);
        sock.connect(ep);
        ba::write(sock, ba::buffer("cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n", 25));
        return;
    }

    BOOST_AUTO_TEST_CASE(testBulk1) {

        boost::test_tools::output_test_stream output;
        {
            cout_redirect guard(output.rdbuf());
            std::size_t bulk = 3;
            short port = 8031;
            boost::asio::io_service io_service;

            AsyncBulkServer server(port, bulk, io_service);

            std::thread input_stream {&Input1};
            io_service.run();
            io_service.stop();
            input_stream.join();

        }
        BOOST_CHECK(output.is_equal ("bulk: cmd1,cmd2,cmd3\n"
                                     "bulk: cmd4,cmd5\n"
        ));
    }

/*
    BOOST_AUTO_TEST_CASE(testBulk1) {

        boost::test_tools::output_test_stream output;
        {
            cout_redirect guard(output.rdbuf());
            short port = 8031;
            boost::asio::io_service io_service;

            ba::ip::tcp::endpoint ep(
                    ba::ip::address::from_string(
                            "127.0.0.1"
                    ),
                    port
            );

            ba::ip::tcp::socket sock(io_service);
            sock.connect(ep);
            ba::write(sock, ba::buffer("cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n", 25));
        }
        BOOST_CHECK(output.is_equal ("bulk: cmd1,cmd2,cmd3\n"
                                        "bulk: cmd4,cmd5\n"
                                        ));
    }
*/
    /*
    BOOST_AUTO_TEST_CASE(testBulk2) {

        boost::test_tools::output_test_stream output;
        {
            cout_redirect guard(output.rdbuf());
            size_t bulk = 3;
            auto h = async::connect(bulk);
            async::receive(h, "cmd1\ncmd2\n{\ncmd3\ncmd4\n}\n{\ncmd5\ncmd6\n{\ncmd7\ncmd8\n}\ncmd9\n}\n{\ncmd10\ncmd11\n", 1);
            async::disconnect(h);
        }
        BOOST_CHECK(output.is_equal ("bulk: cmd1,cmd2\n"
                                        "bulk: cmd3,cmd4\n"
                                        "bulk: cmd5,cmd6,cmd7,cmd8,cmd9\n"
        ));
    }
     */
BOOST_AUTO_TEST_SUITE_END()