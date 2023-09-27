
#include "../include/UDPclient.hpp"

UDPClient::UDPClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port)
    : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), 0)), server_endpoint_(boost::asio::ip::address::from_string(host), port)
{
    this->listening_thread_ = std::thread(&UDPClient::start_listening, this);
}

void UDPClient::send(BinaryProtocole::BinaryMessage msg)
{
    this->socket_.send_to(boost::asio::buffer(protocole.ValueToBin(msg)), server_endpoint_);
}

void UDPClient::update_datas()
{
    std::string message;
    BinaryProtocole::BinaryMessage msg = {type: 1, id: 1, x: 1920, y:1080};

    while (true) {
        std::getline(std::cin, message);
        this->send(msg);
    }
}

void UDPClient::start_listening()
{
    const std::size_t buffer_size = 1024;
    this->recv_buffer_.resize(buffer_size);
    this->read_data();
    this->io_context_.run();
}

void UDPClient::read_data()
{
    this->socket_.async_receive_from(
        boost::asio::buffer(this->recv_buffer_), this->server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                BinaryProtocole::BinaryMessage msg = protocole.BinToValue(this->recv_buffer_);
                std::cout << "Received from server : type:" << msg.type << " id:" << msg.id << " x:" << msg.x << " y:" << msg.y << std::endl;
            }
            this->read_data();
        });
}

UDPClient::~UDPClient()
{
    this->io_context_.stop();
    this->listening_thread_.join();
    this->socket_.close();
}
