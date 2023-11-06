#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../../engine/includes/Ecs.hpp"
#include "../../engine/includes/main.hpp"
#include "../../server/include/BinaryProtocole.hpp"

using boost::asio::ip::udp;

class UDPClient {
public:
    UDPClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port);
    ~UDPClient();

    void send(BinaryProtocole::BinaryMessage msg);
    void start_listening();
    void start(char* arg_game_path);
    void setClientId(uint32_t _clientId) { clientId = _clientId; }
    uint32_t getClientId() { return clientId; }
    std::vector<BinaryProtocole::BinaryMessage> input_queue_;
    void process_input_queue(Ecs &ecs);
    void process_even_input(const BinaryProtocole::BinaryMessage &input, Ecs &ecs);
    void process_odd_input(const BinaryProtocole::BinaryMessage &input);
    void process_remaining_input(Ecs &ecs);

private:
    void read_data();
    void run_game(Ecs &_ecs);
    void retreiveKeyboard();

    boost::asio::io_context& io_context_;
    udp::socket socket_;
    udp::endpoint server_endpoint_;
    std::vector<uint16_t> recv_buffer_;
    BinaryProtocole protocole;
    uint32_t clientId = 0;
    std::vector<int> inputs_;
};
