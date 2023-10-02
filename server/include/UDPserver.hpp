#pragma once

#include <iostream>
#include <thread>
#include <mutex> 
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../../engine/includes/Ecs.hpp"
#include "../../engine/includes/main.hpp"

using boost::asio::ip::udp;

class UDPServer {
    public:
        UDPServer(boost::asio::io_context& io_context, unsigned short port);
        ~UDPServer();

        void start();
        void send_to_all(const std::string& message);

    private:
        void read_data();
        void run_server(Ecs &_ecs);

        boost::asio::io_context& io_context_;
        udp::socket socket_;
        udp::endpoint remote_endpoint_;
        boost::array<char, 1024> recv_buffer_;
        std::map<udp::endpoint, bool> clients_;
};
