#include <cstdlib>
#include <SFML/Network.hpp>
#include "UdpClient.h"

int main(int argc, char** argv)
{
	int difficulty;
	
	if(argc > 1)
	{
		difficulty = atoi(argv[1]);
	}
	else
	{
		difficulty = 1;
	}

	UdpClient client(sf::IpAddress::LocalHost, 55000);
	nlohmann::json data;
	data["event"] = "create_new_game";
	data["data"]["difficulty"] = difficulty;
	client.send(data);
	client.receive();
}
