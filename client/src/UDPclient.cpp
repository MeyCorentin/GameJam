
#include "../include/UDPclient.hpp"

UDPClient::UDPClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port)
    : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), 0)), server_endpoint_(boost::asio::ip::address::from_string(host), port)
{
    inputs_ = {0,0,0,0,0};
    BinaryProtocole::BinaryMessage initial_msg;

    initial_msg = {1, 0, 1920, 1080, 100};
    send(initial_msg);
}

void UDPClient::run_game(Ecs &ecs)
{
    while (true)
    {
        std::pair<int, int> temp;
        int temp_index;
        int temp_value;
        int connected_client = 0;
        auto startTime = std::chrono::high_resolution_clock::now();
        ecs.Update(0);
        retreiveKeyboard();
        auto endTime =  std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
        if (elapsedTime < (1.0 / 60))
            std::this_thread::sleep_for(std::chrono::duration<double>((1.0 / 60) - elapsedTime));
        if (!input_queue_.empty())
        {
            std::pair<int, int> input = input_queue_.front();
            if (input.second % 2 == 0)
            {
                if (input.second == 100)
                {
                    if (input.first !=  clientId)
                    {
                        ecs.scene_.AddNewPlayer(input.first);
                        std::cout << "---- ADD NEW PLAYER" << std::endl;
                    }
                } else {
                    temp = input;
                    input_queue_.push_back(std::make_pair(temp.first, temp.second));
                }
            } else {
                for (auto it = input_queue_.begin(); it != input_queue_.end();) {
                    if (it->first == input.first && it->second == input.second - 1) {
                        it = input_queue_.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
            input_queue_.erase(input_queue_.begin());
            for (auto it = input_queue_.begin(); it != input_queue_.end();++it)
                if (it->second % 2 == 0)
                {
                    int value_1 = it->first;
                    int value_2 = it->second;
                    BinaryProtocole::BinaryMessage msg = {1, (uint32_t)it->first, 1920, 1080, (uint16_t)it->second};
                    ecs.scene_.InputFromPlayer(*it);
                }
        }
    }
}

void UDPClient::retreiveKeyboard()
{
    BinaryProtocole::BinaryMessage msg = {1, getClientId(), 1920, 1080, 0};

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
    run_game(ecs);
}

void UDPClient::read_data()
{
    this->socket_.async_receive_from(
        boost::asio::buffer(this->recv_buffer_), this->server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            BinaryProtocole::BinaryMessage msg = protocole.BinToValue(this->recv_buffer_);

            if (msg.data == 101)
                setClientId(msg.id);
            switch (msg.data)
            {
                case 100:
                        input_queue_.push_back(std::make_pair(msg.id, 100));
                    break;
                case 200:
                    input_queue_.push_back(std::make_pair(msg.id, 200));
                    std::cout << "Client " << msg.id << " press up." << std::endl;
                    break;
                case 210:
                    input_queue_.push_back(std::make_pair(msg.id, 210));
                    std::cout << "Client " << msg.id << " press left." << std::endl;
                    break;
                case 220:
                    input_queue_.push_back(std::make_pair(msg.id, 220));
                    std::cout << "Client " << msg.id << " press down." << std::endl;
                    break;
                case 230:
                    input_queue_.push_back(std::make_pair(msg.id, 230));
                    std::cout << "Client " << msg.id << " press right." << std::endl;
                    break;
                case 300:
                    input_queue_.push_back(std::make_pair(msg.id, 300));
                    std::cout << "Client " << msg.id << " press shoot." << std::endl;
                    break;
                case 201:
                    input_queue_.push_back(std::make_pair(msg.id, 201));
                    std::cout << "Client " << msg.id << " release up." << std::endl;
                    break;
                case 211:
                    input_queue_.push_back(std::make_pair(msg.id, 211));
                    std::cout << "Client " << msg.id << " release left." << std::endl;
                    break;
                case 221:
                    input_queue_.push_back(std::make_pair(msg.id, 221));
                    std::cout << "Client " << msg.id << " release down." << std::endl;
                    break;
                case 231:
                    input_queue_.push_back(std::make_pair(msg.id, 231));
                    std::cout << "Client " << msg.id << " release right." << std::endl;
                    break;
                case 301:
                    input_queue_.push_back(std::make_pair(msg.id, 301));
                    std::cout << "Client " << msg.id << " release shoot." << std::endl;
                    break;
                default:
                    std::cerr << "Unknown message data: " << msg.data << std::endl;
                    break;
            }
            read_data();
        });
}

UDPClient::~UDPClient()
{
    this->socket_.close();
}
