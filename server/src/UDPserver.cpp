#include "../include/UDPserver.hpp"

UDPServer::UDPServer(boost::asio::io_context& io_context, unsigned short port)
    : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), port))
{

}

void UDPServer::start()
{
    this->read_data();
}

void UDPServer::send_to_all(const std::string& message)
{
    for (const auto& [client_endpoint, _] : clients_) {
        this->socket_.send_to(boost::asio::buffer(message), client_endpoint);
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
                this->send_to_all(receivedData);

            }
            this->read_data();
        });
}

UDPServer::~UDPServer()
{
    this->socket_.close();
}
