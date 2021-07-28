#pragma once

#include <vector>
#include <SFML/System.hpp>
#include "Cell.h"
#include <nlohmann/json.hpp>

class GameState
{
public:
	explicit GameState(int difficulty);
	GameState(int width, int height, int mineCount);

	// returns nullptr if position is outside the board
	Cell* getCell(int x, int y);

	bool hasMine(int x, int y);
	
	[[nodiscard]] nlohmann::json serialize() const;
	static GameState deserialize(const nlohmann::json& json);
    void selectCell(int posX, int posY);
    bool hasWon();

    int winState = 0;

private:
    int _bombCount;
	std::vector<Cell> _board;
	int _width;
	int _height;
	
	void initBoard(int mineCount);
	
	GameState(int width, int height);

};
