#include <cstdlib>
#include <SFML/Network.hpp>
#include "UdpClient.h"
#include "MainWindow.h"
#include <SFML/Graphics.hpp>

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

	auto client = new UdpClient(sf::IpAddress::LocalHost, 55000);
	nlohmann::json data;
	data["event"] = "create_new_game";
	data["data"]["difficulty"] = difficulty;
	client->send(data);
	auto received = client->receive();
	auto gameData = nlohmann::json::parse(received);
	if(gameData.contains("user_id")){
	    client->clientId = gameData["user_id"].get<int>();
	}
	//std::cout << data.dump() << std::endl;

	int width = gameData["width"];
	int height = gameData["height"];

    GameState gameState = GameState::deserialize(gameData);

	MainWindow window(width, height, gameState);
    window.run(client);
}
