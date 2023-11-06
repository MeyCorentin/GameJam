#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../../engine/includes/Ecs.hpp"
#include "../../engine/includes/main.hpp"
#include "BinaryProtocole.hpp"
#include <queue>
using boost::asio::ip::udp;

class UDPServer {
    public:
        UDPServer(boost::asio::io_context& io_context, unsigned short port);
        ~UDPServer();

        void start(char *arg_path);
        void send(BinaryProtocole::BinaryMessage msg);
        void send_to_all(BinaryProtocole::BinaryMessage msg);
        void send_to_other(BinaryProtocole::BinaryMessage msg);
        void send_to_last(BinaryProtocole::BinaryMessage msg);
        void start_listening();
        void create_players(int connected_client);
        void send_entity_positions(Ecs &ecs);
        void send_player_positions(Ecs &ecs);
        void process_input_queue(Ecs &ecs);

    private:
        void read_data();
        void handleClientMessage(const BinaryProtocole::BinaryMessage& msg);
        void run_server(Ecs &_ecs);
        std::vector<std::pair<int,int>> input_queue_;
        std::mutex queue_mutex_;
        boost::asio::io_context& io_context_;
        udp::socket socket_;
        udp::endpoint remote_endpoint_;
        std::vector<uint16_t> recv_buffer_;
        std::map<udp::endpoint, uint32_t> clients_;
        uint32_t next_client_id_ = 1;
        BinaryProtocole protocole;
};
