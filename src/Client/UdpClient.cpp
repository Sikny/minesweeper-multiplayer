#include "UdpClient.h"

UdpClient::UdpClient(sf::IpAddress serverIp, int serverPort)
    : _serverIp(serverIp), _serverPort(serverPort) {

}

void UdpClient::send(const nlohmann::json &message) {
    sf::Packet packet = sf::Packet();
    packet << message.dump();
    if(_socket.send(packet, _serverIp, _serverPort) == sf::Socket::Done){
        std::cout << "Sending message '" << message.dump() << "'" << std::endl;
    } else {
        std::cerr << "Error sending message to " << _serverIp << ":" << _serverPort << std::endl;
        sf::sleep(sf::milliseconds(100));
    }
}

std::string UdpClient::receive() {
    sf::Packet packet = sf::Packet();
    sf::IpAddress ipAddress = sf::IpAddress();
    unsigned short port = 0;
    if(_socket.receive(packet, ipAddress, port) == sf::Socket::Done){
        std::string message;
        packet >> message;
        std::cout << "Received message '" << message << "'" << std::endl;
        return message;
    } else {
        sf::sleep(sf::milliseconds(100));
        return std::string();
    }
}

