#pragma once

#include <vector>
#include "Cell.h"

class GameState
{
public:
	GameState(int width, int height, int mineCount);
	
	// returns nullptr if position is outside the board
	Cell* getCell(int x, int y);
	
	bool hasMine(int x, int y);

private:
	std::vector<Cell> _board;
	int _width;
	int _height;
	
	void initBoard(int mineCount);
};
