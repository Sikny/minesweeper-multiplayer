#include "Game.h"
#include <random>
#include <format>

Game::Game(int difficulty) {
    int mineCount;
    switch (difficulty) {
        case 1:
            _width = _height = 8;
            mineCount = 10;
            break;
        case 2:
            _width = _height = 16;
            mineCount = 40;
            break;
        case 3:
            _width = 30;
            _height = 16;
            mineCount = 99;
            break;
        default:
            throw std::invalid_argument(std::format("Invalid difficulty number: {}", difficulty));
    }
    _board.resize(_width * _height);
    initBoard(mineCount);
}

void Game::initBoard(int mineCount) {
    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_int_distribution distX(0, _width - 1);
    std::uniform_int_distribution distY(0, _height - 1);
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

Cell *Game::getCell(int x, int y) {
    if (x < 0 || x >= _width)
        return nullptr;

    if (y < 0 || y >= _height)
        return nullptr;

    return &_board[y * _width + x];
}

nlohmann::json Game::data() {
    nlohmann::json result;
    std::vector<nlohmann::json> board;
    for(Cell& cell : _board){
        board.push_back(cell.data());
    }
    result["board"] = board;
    result["width"] = _width;
    result["height"] = _height;
    return result;
}
