#include "SFML/Network.hpp"
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    char data[100];
    std::size_t received;
    sf::UdpSocket socket;

    sf::IpAddress sender;
    unsigned short port;
    if(auto err = socket.receive(data, 100, received, sender, port) != sf::Socket::Done){
        std::cerr << "Error receiving socket data : " << std::endl;
        std::cerr << err << std::endl;
    }
    return 0;
}
