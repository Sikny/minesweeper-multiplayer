#ifndef MINESWEEPERCLIENT_UDPCLIENT_H
#define MINESWEEPERCLIENT_UDPCLIENT_H

#include <iostream>
#include <SFML/Network.hpp>
#include "../Common/json.hpp"

class UdpClient {
public:
    UdpClient(sf::IpAddress serverIp, int serverPort);
    void send(const nlohmann::json& message);
    std::string receive();
    void close();
private:
    const sf::IpAddress _serverIp;
    const int _serverPort;
    sf::UdpSocket _socket;
};


#endif //MINESWEEPERCLIENT_UDPCLIENT_H
