#include "MainWindow.h"

MainWindow::MainWindow(int boardW, int boardH) : _cellSize(30.0f), _boardWidth(boardW), _boardHeight(boardH),
                                                 _window(sf::VideoMode(_cellSize * _boardWidth + _cellSize * 2, _cellSize * boardH + _cellSize * 2),
            "Minesweeper"){
    _font = new sf::Font();
    _font->loadFromFile("arial.ttf");
    for(int i = 0; i < _boardHeight; ++i){
        for(int j = 0; j < _boardWidth; ++j){
            _cellRenderers.emplace_back(CellRenderer(_cellSize, sf::Vector2f(j, i), _font));
        }
    }
}

MainWindow::~MainWindow() {
    delete _font;
}

void MainWindow::run() {
    while(_window.isOpen()){
        processEvents();
        update();
        render();
    }
}

void MainWindow::processEvents() {
    sf::Event event{};
    while(_window.pollEvent(event)){
        if(event.type == sf::Event::Closed)
            _window.close();
        else if(event.type == sf::Event::MouseButtonPressed){
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            // todo select here
        } else if(event.type == sf::Event::MouseMoved){
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            // todo hover here
        }
    }
}

void MainWindow::update() {
    // todo get gamestate from server
    GameState gameState(_boardWidth, _boardHeight, 10);
    for(int i = 0; i < _boardHeight; ++i){
        for(int j = 0; j < _boardWidth; ++j){
            Cell* cell = gameState.getCell(j, i);
            _cellRenderers[j * _boardWidth + i];
            // todo update status here
        }
    }
}

void MainWindow::render() {
    _window.clear();
    for(auto & _cellRenderer : _cellRenderers){
        _cellRenderer.draw(_window);
    }
    _window.display();
}

