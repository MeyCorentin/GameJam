#include "../include/UDPserver.hpp"

UDPServer::UDPServer(boost::asio::io_context& io_context, unsigned short port)
    : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), port))
{

}


void UDPServer::run_server(Ecs &_ecs)
{
    while (true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        _ecs.update();
        auto endTime =  std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
        if (elapsedTime < (1.0 / 60))
            std::this_thread::sleep_for(std::chrono::duration<double>((1.0 / 60) - elapsedTime));
    }
}

void UDPServer::read_data()
{
    this->socket_.async_receive_from(
        boost::asio::buffer(this->recv_buffer_), this->remote_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                this->clients_[this->remote_endpoint_] = true;
                std::string receivedData(this->recv_buffer_.data(), bytes_recvd);
                std::cout << "Received: " << receivedData << std::endl;
                this->socket_.send_to(boost::asio::buffer("ok"), this->remote_endpoint_);
            }
            read_data();
        });
}

void UDPServer::start()
{
    Ecs _ecs;
    _ecs.create();
    std::thread t1(&UDPServer::read_data, this);
    std::thread t2(&UDPServer::run_server, this, std::ref(_ecs));
    t1.join();
    t2.join();
}


void UDPServer::send_to_all(const std::string& message)
{
    Ecs _ecs;
    _ecs.create();
    for (const auto& [remote_endpoint_, _] : clients_) {
        this->socket_.send_to(boost::asio::buffer(message), this->remote_endpoint_);
        _ecs.update();
    }
}


UDPServer::~UDPServer()
{
    this->socket_.close();
}
