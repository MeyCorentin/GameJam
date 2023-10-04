
#include "../include/UDPclient.hpp"

UDPClient::UDPClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port)
    : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), 0)), server_endpoint_(boost::asio::ip::address::from_string(host), port)
{
    BinaryProtocole::BinaryMessage initial_msg = {type: 1, id: 1, x: 1920, y: 1080, data: 101};
    send(initial_msg);
    start_listening();
}


void UDPClient::run_game(Ecs &ecs)
{
    while (true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        ecs.Update();
        auto endTime =  std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
        if (elapsedTime < (1.0 / 60))
            std::this_thread::sleep_for(std::chrono::duration<double>((1.0 / 60) - elapsedTime));
    }
}

void UDPClient::send(BinaryProtocole::BinaryMessage msg)
{
    this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), server_endpoint_);
}

void UDPClient::start_listening()
{
    const std::size_t buffer_size = 1024;

    this->recv_buffer_.resize(buffer_size);
    read_data();
    this->io_context_.run();
}

void UDPClient::start()
{
    Ecs ecs;

    ecs.Create();
    std::thread t1(&UDPClient::start_listening, this);
    // std::thread t2(&UDPClient::run_game, this, std::ref(_ecs));
    // t1.join();
    run_game(ecs);
    // t2.join();
}

void UDPClient::read_data()
{
    this->socket_.async_receive_from(
        boost::asio::buffer(this->recv_buffer_), this->server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                BinaryProtocole::BinaryMessage msg = protocole.BinToValue(this->recv_buffer_);
                std::cout << "Received from server : type:" << msg.type << " id:" << msg.id << " x:" << msg.x << " y:" << msg.y << " data:" << msg.data << std::endl;
            }
            this->read_data();
        });
}

UDPClient::~UDPClient()
{
    this->socket_.close();
}
