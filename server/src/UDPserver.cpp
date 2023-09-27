#include "../include/UDPserver.hpp"

UDPServer::UDPServer(boost::asio::io_context& io_context, unsigned short port)
    : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), port))
{

}

void UDPServer::start()
{
    const std::size_t buffer_size = 1024;
    this->recv_buffer_.resize(buffer_size);
    this->read_data();
}

void UDPServer::send_to_all(BinaryProtocole::BinaryMessage msg)
{
    for (const auto& [client_endpoint, _] : clients_) {
        this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), client_endpoint);
    }
}

void UDPServer::read_data()
{
    this->socket_.async_receive_from(
        boost::asio::buffer(this->recv_buffer_), this->remote_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                this->clients_[this->remote_endpoint_] = true;
                BinaryProtocole::BinaryMessage msg = protocole.BinToValue(this->recv_buffer_);
                std::cout << "Received : type:" << msg.type << " id:" << msg.id << " x:" << msg.x << " y:" << msg.y << std::endl;
                this->send_to_all(msg);

            }
            this->read_data();
        });
}

UDPServer::~UDPServer()
{
    this->socket_.close();
}
