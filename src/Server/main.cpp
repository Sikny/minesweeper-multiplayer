#include "UdpServer.h"

int main()
{
    UdpServer server(sf::IpAddress::Any, 55000);
    server.run();
    return 0;
}