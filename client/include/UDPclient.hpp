#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <thread>
#include "../../server/include/BinaryProtocole.hpp"

using boost::asio::ip::udp;

class UDPClient {
public:
    UDPClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port);
    ~UDPClient();

    void send(const std::string& message);
    void start_listening();
    void read_data();
    void update_datas();

private:

    boost::asio::io_context& io_context_;
    udp::socket socket_;
    udp::endpoint server_endpoint_;
    boost::array<char, 1024> recv_buffer_;
    std::thread listening_thread_;
    BinaryProtocole protocole;
};

#endif
