#include "../include/UDPserver.hpp"

UDPServer::UDPServer(boost::asio::io_context& io_context, unsigned short port)
    : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), port))
{

}
void UDPServer::run_server(Ecs &ecs, uint32_t lobby)
{
    std::pair<int, int> temp;
    std::vector<std::pair<int, int>> temp_queue;
    int temp_index;
    int temp_value;
    int connected_client = 0;
    int loop_client = 0;

    std::thread send_positions_thread([&]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            send_player_positions(ecs, lobby);
        }
    });

    while (true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        ecs.Update(1);
        auto endTime =  std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();

        if (elapsedTime < (1.0 / 60))
            std::this_thread::sleep_for(std::chrono::duration<double>((1.0 / 60) - elapsedTime));
        if (connected_client < clients_.size())
        {
            ecs.scene_.AddNewPlayer(clientsArray[lobby - 1].size());
            BinaryProtocole::BinaryMessage msg_new_player = {1, static_cast<uint32_t>(clientsArray[lobby - 1].size()), 1920, 1080, 100};
            send_to_other(msg_new_player, lobby);
            connected_client++;
            create_players(connected_client, lobby);
            send_entity_positions(ecs);
            send_player_positions(ecs, lobby);
        }
        if (!input_queue_.empty())
            process_input_queue(ecs, lobby);
    }

    send_positions_thread.join();
}

void UDPServer::create_players(int connected_client, uint32_t lobby)
{
    int loop_client;

    for (loop_client = 1; loop_client != connected_client; loop_client++)
    {
        BinaryProtocole::BinaryMessage msg_create_player = {1, static_cast<uint32_t>(loop_client), 1920, 1080, 100};
        send_to_last(msg_create_player, lobby);
    }
}

void UDPServer::send_entity_positions(Ecs &ecs)
{
    std::cout << "-- ENTITY POSITION --" << std::endl;
    std::vector<EntityPosition> entity_position_list = ecs.scene_.GetEntityPosition();
    for (const auto& position : entity_position_list)
        std::cout << position.id << " | " << position.base_id << " | " << position.x_position << " | "<< position.y_position << std::endl;
}

void UDPServer::send_player_positions(Ecs &ecs, uint32_t lobby)
{
    std::vector<EntityPosition> player_position_list = ecs.scene_.GetPlayerPosition();
    BinaryProtocole::BinaryMessage msg_position_player;
    for (const auto& position : player_position_list)
    {
        msg_position_player.type = 1;
        msg_position_player.id = static_cast<uint32_t>(position.id);
        msg_position_player.x = static_cast<uint16_t>(position.x_position);
        msg_position_player.y = static_cast<uint16_t>(position.y_position);
        msg_position_player.data = 0;
        send_to_all(msg_position_player, lobby);
    }
}

void UDPServer::process_input_queue(Ecs &ecs, uint32_t lobby)
{
    std::pair<int, int> input = input_queue_final[lobby - 1].front();
    std::pair<int, int> temp;
    for (auto it = input_queue_final[lobby - 1].begin(); it != input_queue_final[lobby - 1].end(); ++it)
    {
        if (it->second % 2 == 0 || it->second == 301)
        {
            BinaryProtocole::BinaryMessage msg = {1, static_cast<uint32_t>(it->first), 1920, 1080, static_cast<uint16_t>(it->second)};
            ecs.scene_.InputFromPlayer(*it);
        }
    }
    if (input.second % 2 == 0)
    {
            temp = input;
            input_queue_final[lobby - 1].erase(input_queue_.begin());
            input_queue_final[lobby - 1].push_back(std::make_pair(temp.first, temp.second));
    }
    if (input.second % 2 == 1)
    {
        for (auto it = input_queue_final[lobby - 1].begin(); it != input_queue_final[lobby - 1].end();)
        {
            if (it->first == input.first && it->second == input.second - 1)
                it = input_queue_.erase(it);
            else
                ++it;
        }
        input_queue_final[lobby - 1].erase(input_queue_final[lobby - 1].begin());
    }
}


void UDPServer::start_listening(uint32_t lobby)
{
    const std::size_t buffer_size = 1024;

    this->recv_buffer_.resize(buffer_size);
    read_data(lobby);
    this->io_context_.run();
}

void UDPServer::read_data(uint32_t lobby)
{
    this->socket_.async_receive_from(
        boost::asio::buffer(this->recv_buffer_), this->remote_endpoint_,
        [this, lobby](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                BinaryProtocole::BinaryMessage msg = protocole.BinToValue(this->recv_buffer_);
                // std::cout << "Received : type:" << msg.type << " id:" << msg.id << " x:" << msg.x << " y:" << msg.y << " data:" << msg.data << std::endl;
                if (msg.type == 1)
                    handleClientMessage(msg, lobby);
            }
            read_data(lobby);
    });
}

void UDPServer::handleClientMessage(const BinaryProtocole::BinaryMessage& msg, uint32_t lobby)
{

    std::lock_guard<std::mutex> lock(queue_mutex_);
    switch (msg.data)
    {
        case 100: // Client connection
            if (clientsArray[msg.data - 1].find(remote_endpoint_) == clientsArray[msg.data - 1].end()) {
                clientsArray[msg.data][remote_endpoint_] = next_client_id_array[msg.data - 1]++;
                std::cout << "New client with ID: " << clientsArray[msg.data - 1][remote_endpoint_] << std::endl;
                // Send client ID back
                BinaryProtocole::BinaryMessage response = {1, clientsArray[msg.data][remote_endpoint_], 0, 0, 1000};
                send(response);
            }
            break;
        case 1000:
            input_queue_final[0].push_back(std::make_pair(msg.id, 1000));
            std::cout << "Client " << msg.id << " press up." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 2000:
            input_queue_final[1].push_back(std::make_pair(msg.id, 2000));
            std::cout << "Client " << msg.id << " press up." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 3000:
            input_queue_final[2].push_back(std::make_pair(msg.id, 3000));
            std::cout << "Client " << msg.id << " press up." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 4000:
            input_queue_final[3].push_back(std::make_pair(msg.id, 4000));
            std::cout << "Client " << msg.id << " press up." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 200:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 200));
            std::cout << "Client " << msg.id << " press up." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 210:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 210));
            std::cout << "Client " << msg.id << " press left." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 220:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 220));
            std::cout << "Client " << msg.id << " press down." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 230:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 230));
            std::cout << "Client " << msg.id << " press right." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 300:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 300));
            std::cout << "Client " << msg.id << " press shoot." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 201:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 201));
            std::cout << "Client " << msg.id << " release up." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 211:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 211));
            std::cout << "Client " << msg.id << " release left." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 221:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 221));
            std::cout << "Client " << msg.id << " release down." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 231:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 231));
            std::cout << "Client " << msg.id << " release right." << std::endl;
            send_to_other(msg, lobby);
            break;
        case 301:
            input_queue_final[msg.data - 1].push_back(std::make_pair(msg.id, 301));
            std::cout << "Client " << msg.id << " release shoot." << std::endl;
            send_to_other(msg, lobby);
            break;
        default:
            std::cerr << "Unknown message data: " << msg.data << std::endl;
            break;
    }
}

void UDPServer::start(char *arg_path, uint32_t lobby)
{
    std::thread t1(&UDPServer::start_listening, this, lobby);
    while (clients_.size() == 0);
    Ecs ecs;
    ecs.Create(1, arg_path);
    run_server(ecs, lobby);
}

void UDPServer::send(BinaryProtocole::BinaryMessage msg)
{
    this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), this->remote_endpoint_);
}



void UDPServer::send_to_all(BinaryProtocole::BinaryMessage msg, uint32_t lobby)
{
    for (const auto& [client_endpoint, id] : clientsArray[lobby - 1])
        this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), client_endpoint);
}

void UDPServer::send_to_other(BinaryProtocole::BinaryMessage msg, uint32_t lobby)
{
    for (const auto& [client_endpoint, id] : clientsArray[lobby - 1])
    {
        if (id != msg.id)
            this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), client_endpoint);
    }
}

void UDPServer::send_to_last(BinaryProtocole::BinaryMessage msg, uint32_t lobby)
{
    std::cout << "SEND TO LAST : " << msg.data << std::endl;
    if (!clientsArray[lobby - 1].empty())
    {
        auto last_client = clientsArray[lobby - 1].rbegin();
        if (last_client->second != msg.id)
            this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), last_client->first);
    }
}

UDPServer::~UDPServer()
{
    this->socket_.close();
}
