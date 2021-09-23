#pragma once

#include <cstddef>
#include "CommandInterpreter.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/bind.hpp>


class Server
{
private:
    DataBase mDB;
    CommandInterpreter mCI;

public:

    string receive(string s)
    {
        return mCI.interpret(s, mDB);
    }

};

/*
using handle_t = void *;
using boost::asio::ip::tcp;

class AsyncBulkSession
        : public std::enable_shared_from_this<AsyncBulkSession>
{
public:
    AsyncBulkSession(tcp::socket socket, MultithreadCommandParser& parser)
            : mSocket(std::move(socket)), mParser(parser)
    {
    }

    void start()
    {
        do_read();
    }

private:
    void do_read()
    {
        auto self(shared_from_this());
        mSocket.async_read_some(boost::asio::buffer(mData, max_length),
                                [this, self](boost::system::error_code ec, [[maybe_unused]]std::size_t length)
                                {
                                    if (!ec)
                                    {
                                        std::string in = mData;
                                        mParser.ReceiveInput(in);
                                    }
                                });
    }

    tcp::socket mSocket;
    enum { max_length = 1024 };
    char mData[max_length];
    MultithreadCommandParser& mParser;
};

class AsyncBulkServer {
private:
    MultithreadCommandParser mParser;
    tcp::acceptor mAcceptor;
    tcp::socket mSocket;

public:
    AsyncBulkServer(short port, std::size_t bulk, boost::asio::io_service& io_service) :
    mParser(bulk),
    mAcceptor(io_service, tcp::endpoint(tcp::v4(), port)),
    mSocket(io_service)
    {
        do_accept();
    }

    void do_accept() {
        mAcceptor.async_accept(
                mSocket,
                boost::bind(&AsyncBulkServer::handle_accept, this,
                        boost::asio::placeholders::error));
    }

    void handle_accept(const boost::system::error_code& error)
    {
        if (!error)
        {
            std::make_shared<AsyncBulkSession>(std::move(mSocket), mParser)->start();
            do_accept();
        }
    }

    void receive(handle_t handle, const char *data, [[maybe_unused]]std::size_t size) {
        std::string in = data;
        MultithreadCommandParser *M = reinterpret_cast<MultithreadCommandParser *>(handle);
        M->ReceiveInput(in);
        return;
    }
};

 */

