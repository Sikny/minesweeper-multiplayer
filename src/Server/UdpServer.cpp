#include <iostream>
#include <nlohmann/json.hpp>
#include "UdpServer.h"

int UdpServer::_lastClientId;

UdpServer::UdpServer(sf::IpAddress serverIp, int serverPort)
    : _serverIp(serverIp), _serverPort(serverPort), _running(true), _currentGame(nullptr) {
    _lastClientId = 0;
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
            packet.clear();
            auto json = nlohmann::json::parse(data);
            std::string eventType = json["event"];
            auto eventData = json["data"];

            // if no id, create one, send it to client and increase lastClientId
            int userId;
            if(!json.contains("user_id")){
                userId = _lastClientId++;
                Client client;
                client.clientIpAddress = ipAddress;
                client.clientPort = port;
                _clients[userId] = client;
                std::cout << "client connected with ip " << ipAddress << ", id attributed " << userId << std::endl;
            } else {
                userId = json["user_id"].get<int>();
            }

            nlohmann::json dataSent;
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
            if(_currentGame != nullptr){
                if(eventType == "player_input"){
                    // get input
                    int cellX = eventData["cell"][0].get<int>();
                    int cellY = eventData["cell"][1].get<int>();
                    _currentGame->selectCell(cellX, cellY);
                    if(_currentGame->hasWon()){
                        _currentGame->winState = 1;
                    }
                }
                dataSent = _currentGame->serialize();
            }
            dataSent["user_id"] = userId;
            packet << dataSent.dump();
            if(_socket.send(packet, ipAddress, port) == sf::Socket::Done){
                //std::cout << "Game state sent" << std::endl;
            }
            if(_currentGame != nullptr && _currentGame->winState != 0){
                // game ended, either win or lose
                _currentGame = nullptr;
                std::cout << "Game ended" << std::endl;
            }
        }
    }
}

UdpServer::~UdpServer()
{

}
