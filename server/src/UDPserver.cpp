#include "../include/UDPserver.hpp"

UDPServer::UDPServer(boost::asio::io_context& io_context, unsigned short port)
    : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), port))
{

}

void UDPServer::run_server(Ecs &ecs)
{
    std::pair<int, int> temp;
    std::vector<std::pair<int, int>> temp_queue;
    int temp_index;
    int temp_value;
    int connected_client = 0;
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
            ecs.scene_.AddNewPlayer(clients_.size());
            BinaryProtocole::BinaryMessage msg = {type: 1, id: clients_.size(), x: 1920, y: 1080, data: 100};
            send_to_all(msg);
            connected_client++;
        }
        if (!input_queue_.empty())
        {
            std::pair<int, int> input = input_queue_.front();
            if (input.second % 2 == 0)
            {
                temp = input;
                input_queue_.erase(input_queue_.begin());
                input_queue_.push_back(std::make_pair(temp.first, temp.second));
            } else {
                for (auto it = input_queue_.begin(); it != input_queue_.end();) {
                    if (it->first == input.first && it->second == input.second - 1) {
                        it = input_queue_.erase(it);
                    } else {
                        ++it;
                    }
                }
                input_queue_.erase(input_queue_.begin());
            }
            for (auto it = input_queue_.begin(); it != input_queue_.end();++it)
            {
                if (it->second % 2 == 0)
                {
                    BinaryProtocole::BinaryMessage msg = {type: 1, id: it->first, x: 1920, y: 1080, data: it->second};
                    ecs.scene_.InputFromPlayer(*it);
                }
            }
        }
    }
}

void UDPServer::start_listening()
{
    const std::size_t buffer_size = 1024;

    this->recv_buffer_.resize(buffer_size);
    read_data();
    this->io_context_.run();
}

void UDPServer::read_data()
{
    this->socket_.async_receive_from(
        boost::asio::buffer(this->recv_buffer_), this->remote_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                BinaryProtocole::BinaryMessage msg = protocole.BinToValue(this->recv_buffer_);
                // std::cout << "Received : type:" << msg.type << " id:" << msg.id << " x:" << msg.x << " y:" << msg.y << " data:" << msg.data << std::endl;
                if (msg.type == 1)
                    handleClientMessage(msg);
            }
            read_data();
    });
}

void UDPServer::handleClientMessage(const BinaryProtocole::BinaryMessage& msg)
{

    std::lock_guard<std::mutex> lock(queue_mutex_);
    switch (msg.data)
    {
        case 100: // Client connection
            if (clients_.find(remote_endpoint_) == clients_.end()) {
                clients_[remote_endpoint_] = next_client_id_++;
                std::cout << "New client with ID: " << clients_[remote_endpoint_] << std::endl;
                // Send client ID back
                BinaryProtocole::BinaryMessage response = {type: 1, id: clients_[remote_endpoint_], x: 0, y: 0, data: 101};
                send(response);
            }
            break;

        case 200:
            input_queue_.push_back(std::make_pair(msg.id, 200));
            std::cout << "Client " << msg.id << " press up." << std::endl;
            send_to_all(msg);
            break;

        case 210:
            input_queue_.push_back(std::make_pair(msg.id, 210));
            std::cout << "Client " << msg.id << " press left." << std::endl;
            send_to_all(msg);
            break;

        case 220:
            input_queue_.push_back(std::make_pair(msg.id, 220));
            std::cout << "Client " << msg.id << " press down." << std::endl;
            send_to_all(msg);
            break;

        case 230:
            input_queue_.push_back(std::make_pair(msg.id, 230));
            std::cout << "Client " << msg.id << " press right." << std::endl;
            send_to_all(msg);
            break;

        case 300:
            input_queue_.push_back(std::make_pair(msg.id, 300));
            std::cout << "Client " << msg.id << " press shoot." << std::endl;
            send_to_all(msg);
            break;
        case 201:
            input_queue_.push_back(std::make_pair(msg.id, 201));
            std::cout << "Client " << msg.id << " release up." << std::endl;
            send_to_all(msg);
            break;

        case 211:
            input_queue_.push_back(std::make_pair(msg.id, 211));
            std::cout << "Client " << msg.id << " release left." << std::endl;
            send_to_all(msg);
            break;

        case 221:
            input_queue_.push_back(std::make_pair(msg.id, 221));
            std::cout << "Client " << msg.id << " release down." << std::endl;
            send_to_all(msg);
            break;

        case 231:
            input_queue_.push_back(std::make_pair(msg.id, 231));
            std::cout << "Client " << msg.id << " release right." << std::endl;
            send_to_all(msg);
            break;

        case 301:
            input_queue_.push_back(std::make_pair(msg.id, 301));
            std::cout << "Client " << msg.id << " release shoot." << std::endl;
            send_to_all(msg);
            break;

        default:
            std::cerr << "Unknown message data: " << msg.data << std::endl;
            break;
    }
}

void UDPServer::start()
{
    std::thread t1(&UDPServer::start_listening, this);
    while (clients_.size() == 0);
    Ecs ecs;
    ecs.Create(1);
    run_server(ecs);
}

void UDPServer::send(BinaryProtocole::BinaryMessage msg)
{
    this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), this->remote_endpoint_);
}

void UDPServer::send_to_all(BinaryProtocole::BinaryMessage msg)
{
    std::cout << "SEND TO ALL : " << msg.data << std::endl;
    for (const auto& [client_endpoint, id] : clients_)
    {
        if (id != msg.id)
            this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), client_endpoint);
    }
}

UDPServer::~UDPServer()
{
    this->socket_.close();
}
