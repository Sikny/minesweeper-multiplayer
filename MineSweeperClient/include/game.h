#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "case.h"

class Game
{
    public:
        Game(std::string difficulty, int boardSize, int nBombs);
        void run();

    private:
        void processEvents();
        void update();
        void render();
        bool hasWon();

        float cellSize;
        int difficulty, boardSize, nBombs;
        std::string difficulty_str;

        sf::RenderWindow window;

        sf::Font* font;
        Case* board;
};

#endif // GAME_H
