#include "MainWindow.h"

MainWindow::MainWindow(int boardW, int boardH, GameState& firstState) : _cellSize(30.0f),
    _boardWidth(boardW), _boardHeight(boardH), gameState(firstState) {
    _window = new sf::RenderWindow(sf::VideoMode(_cellSize * _boardWidth + _cellSize * 2, _cellSize * _boardHeight + _cellSize * 2),"Minesweeper");
    _font = new sf::Font();
    _font->loadFromFile("resources/arial.ttf");
    for(int i = 0; i < _boardHeight; ++i){
        for(int j = 0; j < _boardWidth; ++j){
            CellRenderer cell(_cellSize, sf::Vector2f((float)i*(_cellSize+1)+_cellSize-(float)_boardWidth/2.0f, (float)j*(_cellSize+1)+_cellSize-(float)_boardHeight/2), _font);
            cell.arrayPosition = sf::Vector2i(i, j);
            _cellRenderers.emplace_back(cell);
        }
    }
}

MainWindow::~MainWindow() {
    delete _font;
    delete _client;
}

void MainWindow::run(UdpClient* client) {
    _client = client;
    while(_window->isOpen()){
        processEvents();
        update();
        render();
    }
}

void MainWindow::processEvents() {
    sf::Event event{};
    while(_window->pollEvent(event)){
        if(event.type == sf::Event::Closed){
            _client->close();
            _window->close();
        }
        else if(event.type == sf::Event::MouseButtonPressed){
            sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
            for(unsigned short i = 0; i < _boardWidth*_boardHeight; i++){
                if(_cellRenderers[i].hasMouseOver(mousePos)){
                    // SEND INPUT HERE
                    nlohmann::json inputData;
                    inputData["event"] = "player_input";
                    inputData["data"]["cell"][0] = _cellRenderers[i].arrayPosition.x;
                    inputData["data"]["cell"][1] = _cellRenderers[i].arrayPosition.y;
                    inputData["user_id"] = _client->clientId;
                    _client->send(inputData);

                    std::string received = _client->receive();
                    nlohmann::json gameData = nlohmann::json::parse(received);
                    gameState = GameState::deserialize(gameData);
                }
            }
        } else if(event.type == sf::Event::MouseMoved){
            sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
            // todo hover here
            for(unsigned short i = 0; i < _boardWidth*_boardHeight; i++){
                if(_cellRenderers[i].hasMouseOver(mousePos)){
                    if(event.type == sf::Event::MouseMoved) _cellRenderers[i].hover();
                }
                else _cellRenderers[i].unhover();
            }
        }
    }
}

void MainWindow::update() {
    for(int i = 0; i < _boardWidth; ++i){
        for(int j = 0; j < _boardHeight; ++j){
            Cell* cell = gameState.getCell(i, j);
            if(cell->activated){
                _cellRenderers[i * _boardWidth + j].color = sf::Color(100, 100, 100);
                if(cell->hasMine){
                    // todo lose
                }
                if(cell->nearbyMines > 0){
                    _cellRenderers[i * _boardWidth + j].setStatus(cell->nearbyMines);
                }
            } else {
                //_cellRenderers[j * _boardWidth + i].color = sf::Color(100, 100, 100);
            }
        }
    }
}

void MainWindow::render() {
    _window->clear();
    for(auto & _cellRenderer : _cellRenderers){
        _cellRenderer.draw(*_window);
    }
    _window->display();
}

