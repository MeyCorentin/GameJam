#ifndef UDPSERVER_HPP
#define UDPSERVER_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <map>

using boost::asio::ip::udp;

class UDPServer {
public:
    UDPServer(boost::asio::io_context& io_context, unsigned short port);
    ~UDPServer();

    void start();
    void send_to_all(const std::string& message);

private:
    void read_data();

    boost::asio::io_context& io_context_;
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1024> recv_buffer_;
    std::map<udp::endpoint, bool> clients_;
};

#endif
