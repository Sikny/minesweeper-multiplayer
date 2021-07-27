#ifndef MINESWEEPERSERVER_GAME_H
#define MINESWEEPERSERVER_GAME_H


#include <vector>
#include <string>
#include "Cell.h"
#include "json.hpp"

class Game {
public:
    explicit Game(int difficulty);

    // returns nullptr if position is outside the board
    Cell* getCell(int x, int y);

    nlohmann::json data();

private:
    int _width;
    int _height;
    std::vector<Cell> _board;

    void initBoard(int mineCount);
};


#endif //MINESWEEPERSERVER_GAME_H
