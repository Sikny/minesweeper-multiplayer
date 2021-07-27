#ifndef MINESWEEPERSERVER_CELL_H
#define MINESWEEPERSERVER_CELL_H

#include "json.hpp"

class Cell {
public:
    bool hasMine = false;
    bool activated = false;
    bool hasFlag = false;
    int nearbyMines = 0;

    nlohmann::json data();
};


#endif //MINESWEEPERSERVER_CELL_H
