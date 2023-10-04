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
                std::cout << "Received data from client" << std::endl;
                this->clients_[this->remote_endpoint_] = true;
                std::string data(this->recv_buffer_.begin(), this->recv_buffer_.end());
                std::cout << "Received from client : " << data << std::endl;
                // BinaryProtocole::BinaryMessage msg = protocole.BinToValue(this->recv_buffer_);
                // std::cout << "Received : type:" << msg.type << " id:" << msg.id << " x:" << msg.x << " y:" << msg.y << " data:" << msg.data << std::endl;
                // this->send_to_all(msg);
                this->socket_.send_to(boost::asio::buffer("ok"), this->remote_endpoint_);
            }
            read_data();
    });
}

void UDPServer::start()
{
    Ecs _ecs;

    _ecs.create();
    std::thread t1(&UDPServer::start_listening, this);
    // std::thread t2(&UDPServer::run_server, this, std::ref(_ecs));
    // t1.join();
    run_server(_ecs);
    // t2.join();
}

void UDPServer::send_to_all(BinaryProtocole::BinaryMessage msg)
{
    Ecs _ecs;

    _ecs.create();
    for (const auto& [client_endpoint, _] : clients_) {
        this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), client_endpoint);
        _ecs.update();
    }
}

UDPServer::~UDPServer()
{
    this->socket_.close();
}
