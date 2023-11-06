
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
        BinaryProtocole::BinaryMessage temp;
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
        process_input_queue(ecs);
    }
}

void UDPClient::process_input_queue(Ecs &ecs)
{
    if (!input_queue_.empty())
    {
        BinaryProtocole::BinaryMessage input = input_queue_.front();
        if (input.data == 301)
        {
            process_even_input(input, ecs);
        }
        if (input.data % 2 == 0)
        {
            process_even_input(input, ecs);
        }
        else
        {
            process_odd_input(input);
        }
        if (input.data != 1000 && input.data != 0 && input.data != 100)
        {
            input_queue_.erase(input_queue_.begin());
            process_remaining_input(ecs);
        }
    }
}

void UDPClient::process_even_input(const BinaryProtocole::BinaryMessage &input, Ecs &ecs)
{
    if (input.data == 100 && input.id != clientId)
    {
        ecs.scene_.AddNewPlayer(input.id);
        input_queue_.erase(input_queue_.begin());
    }
    if (input.data == 1000)
    {
        ecs.scene_.SetClientPlayerId(input.id);
        input_queue_.erase(input_queue_.begin());
    }
    if (input.data == 0)
    {
        ecs.scene_.SetPlayerPosition(input.id, input.x, input.y);
        input_queue_.erase(input_queue_.begin());
    }
    if(input.data != 100 && input.data != 0 && input.data != 1000)
    {
        
        BinaryProtocole::BinaryMessage temp = input;
        input_queue_.push_back(temp);
    }
}

void UDPClient::process_odd_input(const BinaryProtocole::BinaryMessage &input)
{
    for (auto it = input_queue_.begin(); it != input_queue_.end();)
        it = (it->id == input.id && it->data == input.data - 1) ? input_queue_.erase(it) : ++it;
}

void UDPClient::process_remaining_input(Ecs &ecs)
{
    for (auto it = input_queue_.begin(); it != input_queue_.end(); ++it)
    {
        if (it->data % 2 == 0)
        {
            int value_1 = it->id;
            int value_2 = it->data;
            ecs.scene_.InputFromPlayer(std::make_pair((int)it->id, (int)it->data));
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

void UDPClient::start(char* arg_game_path)
{
    Ecs ecs;

    ecs.Create(0, arg_game_path);
    std::thread t1(&UDPClient::start_listening, this);
    run_game(ecs);
}

void UDPClient::read_data()
{
    this->socket_.async_receive_from(
        boost::asio::buffer(this->recv_buffer_), this->server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            BinaryProtocole::BinaryMessage msg = protocole.BinToValue(this->recv_buffer_);

            if (msg.data == 1000)
                setClientId(msg.id);
            switch (msg.data)
            {
                case 0:
                    input_queue_.push_back(msg);
                    break;
                case 100:
                    input_queue_.push_back(msg);
                    break;
                case 1000:
                    input_queue_.push_back(msg); 
                    break;
                case 200:
                    input_queue_.push_back(msg);
                    std::cout << "Client " << msg.id << " press up." << std::endl;
                    break;
                case 210:
                    input_queue_.push_back(msg);
                    std::cout << "Client " << msg.id << " press left." << std::endl;
                    break;
                case 220:
                    input_queue_.push_back(msg);
                    std::cout << "Client " << msg.id << " press down." << std::endl;
                    break;
                case 230:
                    input_queue_.push_back(msg);
                    std::cout << "Client " << msg.id << " press right." << std::endl;
                    break;
                case 300:
                    input_queue_.push_back(msg);
                    std::cout << "Client " << msg.id << " press shoot." << std::endl;
                    break;
                case 201:
                    input_queue_.push_back(msg);
                    std::cout << "Client " << msg.id << " release up." << std::endl;
                    break;
                case 211:
                    input_queue_.push_back(msg);
                    std::cout << "Client " << msg.id << " release left." << std::endl;
                    break;
                case 221:
                    input_queue_.push_back(msg);
                    std::cout << "Client " << msg.id << " release down." << std::endl;
                    break;
                case 231:
                    input_queue_.push_back(msg);
                    std::cout << "Client " << msg.id << " release right." << std::endl;
                    break;
                case 301:
                    input_queue_.push_back(msg);
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
