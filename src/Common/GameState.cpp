#include "GameState.h"
#include <random>
#include <iostream>

GameState::GameState(int difficulty)
{
	switch (difficulty)
	{
		case 1:
			_width = _height = 8;
			_bombCount = 10;
			break;
		case 2:
			_width = _height = 16;
			_bombCount = 40;
			break;
		case 3:
			_width = 30;
			_height = 16;
			_bombCount = 99;
			break;
		default:
			throw std::invalid_argument("Invalid difficulty number: " + std::to_string(difficulty));
	}
	
	_board.resize(_width * _height);
	
	initBoard(_bombCount);
}

GameState::GameState(int width, int height, int mineCount):
GameState(width, height)
{
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
    std::random_device dev;
	std::mt19937 engine(dev());
	std::uniform_int_distribution<> distX(0, _width - 1);
	std::uniform_int_distribution<> distY(0, _height - 1);
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

nlohmann::json GameState::serialize() const
{
	nlohmann::json data;
	
	std::vector<nlohmann::json> board;
	for(int i = 0; i < _board.size(); i++)
	{
		const Cell& cell = _board[i];
		nlohmann::json jsonCell;
		jsonCell["hasMine"] = cell.hasMine;
		jsonCell["activated"] = cell.activated;
		jsonCell["hasFlag"] = cell.hasFlag;
		jsonCell["nearbyMines"] = cell.nearbyMines;
		board.push_back(jsonCell);
	}
	data["board"] = board;
	data["winState"] = winState;
	
	data["width"] = _width;
	data["height"] = _height;
	return data;
}

GameState GameState::deserialize(const nlohmann::json& json)
{
	int width = json["width"].get<int>();
	int height = json["height"].get<int>();
	
	GameState gameState(width, height);
	
	for(int i = 0; i < json["board"].size(); i++)
	{
		nlohmann::json jsonCell = json["board"][i];
		Cell cell;
		cell.hasMine = jsonCell["hasMine"].get<bool>();
		cell.activated = jsonCell["activated"].get<bool>();
		cell.hasFlag = jsonCell["hasFlag"].get<bool>();
		cell.nearbyMines = jsonCell["nearbyMines"];
		gameState._board[i] = cell;
		gameState.winState = json["winState"];
	}
	
	return gameState;
}

GameState::GameState(int width, int height):
_width(width), _height(height)
{
	_board.resize(width * height);
}

void GameState::selectCell(int posX, int posY) {
    Cell* cell = getCell(posX, posY);
    if(cell->activated) return;
    cell->activated = true;
    if(cell->hasMine){
        // todo lose
        std::cout << "LOSE" << std::endl;
        winState = 2;
    } else {
        if(cell->nearbyMines == 0){
            for(int i = posX - 1; i <= posX + 1; ++i){
                for(int j = posY - 1; j <= posY + 1; ++j){
                    if(i >= 0 && i < _width && j >= 0 && j < _height){
                        if(!getCell(i, j)->activated)
                            selectCell(i, j);
                    }
                }
            }
        }
    }
}

bool GameState::hasWon() {
    int solvedCases = 0;
    for(int i = 0; i < _width*_height; i++){
        if(_board[i].activated) solvedCases++;
    }
    return (_width*_height-solvedCases) == _bombCount;
}
