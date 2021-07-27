#include "SFML/Network.hpp"
#include <iostream>
#include <csignal>


using namespace std::string_literals;

namespace
{
    volatile std::atomic<bool> running = true;

    void signal_handler(int)
    {
        running = false;
    }
}

struct Connection
{
    sf::IpAddress IpAddress;
    unsigned short Port;
};

int main()
{
    std::signal(SIGTERM, signal_handler);

    const auto RetryCount = 3;
    const auto ServerIp = sf::IpAddress::Any;
    const auto ServerPort = 55000;

    auto socket = sf::UdpSocket{};

    for (auto connectionTries = 1; socket.bind(ServerPort, ServerIp) != sf::Socket::Done; ++connectionTries)
    {
        if (connectionTries >= RetryCount)
        {
            std::cerr << "Unable to bind on port " << ServerPort << "\n";
            running = false;
            break;
        }
    }

    if (running)
    {
        std::cout << "Binding to " << ServerIp.toString() << ":" << ServerPort << " was successful\n";
        std::cout << "Waiting for client messages...\n";
    }

    while (running)
    {
        auto connection = Connection{};
        auto packet = sf::Packet{};
        if (socket.receive(packet, connection.IpAddress, connection.Port) == sf::Socket::Done)
        {
            auto data = ""s;
            packet >> data;

            std::cout << "== Received (" << connection.IpAddress.toString() << ":" << connection.Port << ") ==\n";
            std::cout << data << "\n";

            auto acknowledgePacket = sf::Packet{};
            acknowledgePacket << "OK\n"s;

            if (socket.send(acknowledgePacket, connection.IpAddress, connection.Port) == sf::Socket::Done)
            {
                std::cout << "== Send Acknowledge (" << connection.IpAddress.toString() << ":" << connection.Port << ") ==\n";
            }
            else
            {
                std::cerr << "Unable to send acknowledge (" << connection.IpAddress.toString() << ":" << connection.Port << ")\n";
            }
        }
        else
        {
            sf::sleep(sf::milliseconds(100));
        }
    }
}