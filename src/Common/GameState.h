#pragma once

#include <vector>
#include "Cell.h"
#include <nlohmann/json.hpp>

class GameState
{
public:
	GameState(int difficulty);
	GameState(int width, int height, int mineCount);

	// returns nullptr if position is outside the board
	Cell* getCell(int x, int y);

	bool hasMine(int x, int y);
	
	nlohmann::json serialize() const;
	static GameState deserialize(const nlohmann::json& json);

private:
	std::vector<Cell> _board;
	int _width;
	int _height;
	
	void initBoard(int mineCount);
	
	GameState(int width, int height);
};
