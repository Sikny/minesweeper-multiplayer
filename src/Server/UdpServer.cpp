#include <iostream>
#include <nlohmann/json.hpp>
#include "UdpServer.h"

UdpServer::UdpServer(sf::IpAddress serverIp, int serverPort)
    : _serverIp(serverIp), _serverPort(serverPort), _running(true), _currentGame(nullptr) {
    if(_socket.bind(_serverPort, _serverIp) != sf::Socket::Done){
        std::cerr << "Unable to bind on port " << _serverPort << std::endl;
    }
    std::cout << "Socket bind" << std::endl;
    std::cout << "Waiting for client messages..." << std::endl;
}

void UdpServer::run() {
    while(_running){
        sf::IpAddress ipAddress;
        unsigned short port;
        sf::Packet packet;
        if(_socket.receive(packet, ipAddress, port) == sf::Socket::Done){
            std::string data;
            packet >> data;
            auto json = nlohmann::json::parse(data);
            std::string eventType = json["event"];
            auto eventData = json["data"];

            if (eventType == "create_new_game")
			{
				if(_currentGame == nullptr)
				{
					// create a game
					int dif = eventData["difficulty"].get<int>();
					std::cout << "Creating game with difficulty " << dif << std::endl;
					_currentGame = std::make_unique<GameState>(dif);
				}
				else
				{
					// do nothing
				}
			}
            
            

            packet.clear();
            packet << _currentGame->serialize().dump();
            if(_socket.send(packet, ipAddress, port) == sf::Socket::Done){
                std::cout << "Game state sent" << std::endl;
            }
        }
    }
}

UdpServer::~UdpServer()
{

}
