#include "GameState.h"
#include <random>

GameState::GameState(int width, int height, int mineCount):
_width(width), _height(height)
{
	_board.resize(width * height);
	
	initBoard(mineCount);
}

Cell* GameState::getCell(int x, int y)
{
	if (x < 0 || x >= _width)
		return nullptr;
	
	if (y < 0 || y >= _height)
		return nullptr;
	
	return &_board[y * _width + x];
}

void GameState::initBoard(int mineCount)
{
	std::mt19937 engine;
	std::uniform_int_distribution distX(0, _width);
	std::uniform_int_distribution distY(0, _height);
	for (int i = 0; i < mineCount;)
	{
		int x = distX(engine);
		int y = distY(engine);
		
		Cell* cell = getCell(x, y);
		
		// this cell already has a mine, try again with another cell
		if (cell->hasMine)
			continue;
		
		cell->hasMine = true;
		i++;
	}
	
	for (int cellY = 0; cellY < _height; cellY++)
	{
		for (int cellX = 0; cellX < _width; cellX++)
		{
			Cell* cell = getCell(cellX, cellY);
			
			for (int y = -1; y <= 1; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					if (x == 0 && y == 0)
						continue;
					
					Cell* neighbor = getCell(cellX + x, cellY + y);
					if (neighbor && neighbor->hasMine)
					{
						cell->nearbyMines++;
					}
				}
			}
		}
	}
}

bool GameState::hasMine(int x, int y)
{
	Cell* cell = getCell(x, y);
	
	return cell && cell->hasMine;
}
