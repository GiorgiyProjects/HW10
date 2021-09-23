#pragma once

#include <cstddef>
#include "CommandInterpreter.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

class Session
        : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, DataBase& db)
            : mSocket(std::move(socket)), mDBref(db)
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
                                        string result = mCI.receive(mData, mDBref);
                                        for (int i = 0; i < max_length; i++) mData[i] = '\0';
                                    }
                                });
    }

    tcp::socket mSocket;
    enum { max_length = 1024 };
    char mData[max_length];
    DataBase& mDBref;
    CommandInterpreter mCI;
};

class Server {
private:
    DataBase mDB;
    CommandInterpreter mCI;

    tcp::acceptor mAcceptor;
    tcp::socket mSocket;

public:
    Server(short port, boost::asio::io_service& io_service) :
            mAcceptor(io_service, tcp::endpoint(tcp::v4(), port)),
            mSocket(io_service)
    {
        do_accept();
    }

    void do_accept() {
        mAcceptor.async_accept(
                mSocket,
                boost::bind(&Server::handle_accept, this,
                            boost::asio::placeholders::error));
    }

    void handle_accept(const boost::system::error_code& error)
    {
        if (!error)
        {
            std::make_shared<Session>(std::move(mSocket), mDB)->start();
            do_accept();
        }
    }
};

