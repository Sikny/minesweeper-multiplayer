#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include "../Common/GameState.h"
#include "CellRenderer.h"

class MainWindow {
public:
    MainWindow(int boardW, int boardH, GameState& firstState);
    ~MainWindow();
    void processEvents();
    void run();
    void update();
    void render();

    GameState gameState;

private:
    sf::RenderWindow* _window;
    sf::Font* _font;
    float _cellSize;
    int _boardWidth;
    int _boardHeight;

    std::vector<CellRenderer> _cellRenderers;
};


#endif //MAINWINDOW_H
