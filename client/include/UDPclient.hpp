#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../../engine/includes/Ecs.hpp"
#include "../../engine/includes/main.hpp"

using boost::asio::ip::udp;

class UDPClient {
public:
    UDPClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port);
    ~UDPClient();

    void send(const std::string& message);
    void start_listening();

private:
    void read_data();
    void run_game(Ecs &_ecs);

    boost::asio::io_context& io_context_;
    udp::socket socket_;
    udp::endpoint server_endpoint_;
    boost::array<char, 1024> recv_buffer_;
};
