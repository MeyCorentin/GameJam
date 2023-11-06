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

        void start(char *arg_path, uint32_t lobby);
        void send(BinaryProtocole::BinaryMessage msg);
        void send_to_all(BinaryProtocole::BinaryMessage msg, uint32_t lobby);
        void send_to_other(BinaryProtocole::BinaryMessage msg, uint32_t lobby);
        void send_to_last(BinaryProtocole::BinaryMessage msg, uint32_t lobby);
        void start_listening(uint32_t lobby);
        void create_players(int connected_client, uint32_t lobby);
        void send_entity_positions(Ecs &ecs);
        void send_player_positions(Ecs &ecs, uint32_t lobby);
        void process_input_queue(Ecs &ecs, uint32_t lobby);

    private:
        void read_data(uint32_t lobby);
        void handleClientMessage(const BinaryProtocole::BinaryMessage& msg, uint32_t lobby);
        void run_server(Ecs &_ecs, uint32_t lobby);

        std::vector<std::pair<int,int>> input_queue_;
        std::array<std::vector<std::pair<int, int>>, 4> input_queue_final;
        //changement en array

        std::mutex queue_mutex_;
        boost::asio::io_context& io_context_;
        udp::socket socket_;
        udp::endpoint remote_endpoint_;
        std::vector<uint16_t> recv_buffer_;

        std::map<udp::endpoint, uint32_t> clients_;
        std::array<std::map<udp::endpoint, uint32_t>, 4> clientsArray;
        //changement en array

        uint32_t next_client_id_ = 1;
        uint32_t next_client_id_array[4] = {1, 1, 1, 1};
        //changement en array
        
        BinaryProtocole protocole;
};
