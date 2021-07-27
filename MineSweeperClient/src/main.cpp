#include <cstdlib>
#include <string>
#include <iostream>
#include <format>
#include <csignal>
#include <SFML/Network.hpp>
#include "GameState.h"
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
	
	int boardWidth;
	int boardHeight;
	int nBombs;
	std::string difficulty_str;
	switch(difficulty)
	{
		case 1:
			boardWidth = 8;
			boardHeight = 8;
			nBombs = 10;
			difficulty_str = "Easy";
			break;
		case 2:
			boardWidth = 16;
			boardHeight = 16;
			nBombs = 40;
			difficulty_str = "Normal";
			break;
		case 3:
			boardWidth = 30;
			boardHeight = 16;
			nBombs = 99;
			difficulty_str = "Hard";
			break;
		default:
			throw std::invalid_argument(std::format("Invalid difficulty number: {}", difficulty));
	}
	
	std::cout << "Difficulty: " << difficulty_str << std::endl;
	std::cout << "Grid: " << boardWidth << 'x' << boardHeight << std::endl;
	std::cout << "Bombs: " << nBombs << std::endl;

	UdpClient client(sf::IpAddress::LocalHost, 55000);
}
