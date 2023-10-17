
#include "../include/UDPclient.hpp"

UDPClient::UDPClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port)
    : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), 0)), server_endpoint_(boost::asio::ip::address::from_string(host), port)
{
    inputs_ = {0,0,0,0,0};
    BinaryProtocole::BinaryMessage initial_msg = {type: 1, id: 0, x: 1920, y: 1080, data: 100};
    send(initial_msg);
}

void UDPClient::run_game(Ecs &ecs)
{
    while (true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        ecs.Update(0);
        retreiveKeyboard();
        auto endTime =  std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
        if (elapsedTime < (1.0 / 60))
            std::this_thread::sleep_for(std::chrono::duration<double>((1.0 / 60) - elapsedTime));
    }
}

void UDPClient::retreiveKeyboard()
{
    BinaryProtocole::BinaryMessage msg = {type: 1, id: getClientId(), x: 1920, y: 1080, data: 0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && inputs_[0] == 0)
    {
        inputs_[0] = 1;
        msg.data = 200;
        send(msg);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && inputs_[1] == 0)
    {
        inputs_[1] = 1;
        msg.data = 210;
        send(msg);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && inputs_[2] == 0)
    {
        inputs_[2] = 1;
        msg.data = 220;
        send(msg);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && inputs_[3] == 0)
    {
        inputs_[3] = 1;
        msg.data = 230;
        send(msg);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && inputs_[4] == 0)
    {
        inputs_[4] = 1;
        msg.data = 300;
        send(msg);
    } else if  (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && inputs_[0] == 1)
    {
        inputs_[0] = 0;
        msg.data = 201;
        send(msg);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && inputs_[1] == 1)
    {
        inputs_[1] = 0;
        msg.data = 211;
        send(msg);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && inputs_[2] == 1)
    {
        inputs_[2] = 0;
        msg.data = 221;
        send(msg);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && inputs_[3] == 1)
    {
        inputs_[3] = 0;
        msg.data = 231;
        send(msg);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && inputs_[4] == 1)
    {
        inputs_[4] = 0;
        msg.data = 301;
        send(msg);
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

    ecs.Create(0);
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

                // Check if the received message is an ID assignment from the server
                if (msg.data == 101) {
                    setClientId(msg.id);
                    std::cout << "Client ID assigned by server: " << getClientId() << std::endl;
                }
            }
            this->read_data();
        });
}

UDPClient::~UDPClient()
{
    this->socket_.close();
}
