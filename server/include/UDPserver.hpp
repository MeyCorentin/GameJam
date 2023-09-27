#ifndef UDPSERVER_HPP
#define UDPSERVER_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <map>

#include "BinaryProtocole.hpp"

using boost::asio::ip::udp;

class UDPServer {
public:
    UDPServer(boost::asio::io_context& io_context, unsigned short port);
    ~UDPServer();

    void start();
    void send_to_all(BinaryProtocole::BinaryMessage msg);

private:
    void read_data();

    boost::asio::io_context& io_context_;
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::vector<uint16_t> recv_buffer_;
    std::map<udp::endpoint, bool> clients_;
    BinaryProtocole protocole;
};

#endif
