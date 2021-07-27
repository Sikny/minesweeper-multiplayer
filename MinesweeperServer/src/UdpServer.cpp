#include <iostream>
#include "json.hpp"
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
        sf::Packet packet = sf::Packet();
        if(_socket.receive(packet, ipAddress, port) == sf::Socket::Done){
            std::string data;
            packet >> data;
            auto jsonData = nlohmann::json::parse(data);

            auto difficulty = jsonData.find("difficulty");
            if(difficulty != jsonData.end()){
                if(_currentGame == nullptr){
                // creating game
                    int dif = difficulty.value();
                    std::cout << "Creating game with difficulty " << dif << std::endl;
                    _currentGame = new Game(dif);
                } else {
                    // nothing to do here
                    std::cout << jsonData << std::endl;
                }
            } else {
                // get input
                std::cout << jsonData << std::endl;
            }

            packet.clear();
            packet << _currentGame->data().dump();
            if(_socket.send(packet, ipAddress, port) == sf::Socket::Done){
                std::cout << "Game state sent" << std::endl;
            }
        }
    }
}

UdpServer::~UdpServer() {
    delete _currentGame;
}
