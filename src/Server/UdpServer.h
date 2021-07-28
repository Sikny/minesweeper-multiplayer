#ifndef MINESWEEPERSERVER_UDPSERVER_H
#define MINESWEEPERSERVER_UDPSERVER_H

#include <SFML/Network.hpp>
#include "../Common/GameState.h"
#include "Client.h"

class UdpServer {
public:
    UdpServer(sf::IpAddress serverIp, int serverPort);
    ~UdpServer();
    void run();
private:
    const sf::IpAddress _serverIp;
    const int _serverPort;
    sf::UdpSocket _socket;

    bool _running;

    std::unique_ptr<GameState> _currentGame;

    static int _lastClientId;

    std::map<int, Client> _clients;
};


#endif //MINESWEEPERSERVER_UDPSERVER_H
