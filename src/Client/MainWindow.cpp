
#include "MainWindow.h"

MainWindow::MainWindow(int boardW, int boardH, GameState& firstState)
    : _cellSize(30.0f), _boardWidth(boardW), _boardHeight(boardH), gameState(firstState), _updateGame(true) {
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
    _clock.restart();
}

MainWindow::~MainWindow() {
    delete _font;
    delete _client;
}

void MainWindow::run(UdpClient* client) {
    _client = client;
    while(_window->isOpen()){
        if(_updateGame){
            processEvents();
            update();
            render();
        }
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
    if(gameState.winState != 0){
        std::cout << "LOSE" << std::endl;
        // game ended
        _updateGame = false;

        sf::RenderWindow dialog(sf::VideoMode(150, 50), "Game ended");
        sf::Text result;
        if(gameState.winState == 1){
            result.setString("YOU WIN !");
        } else if(gameState.winState == 2){
            result.setString("YOU LOSE !");
        }
        result.setFont(*_font);
        result.setCharacterSize(20);
        result.setPosition(10, 10);
        result.setFillColor(sf::Color::White);
        while(dialog.isOpen()){
            dialog.clear();
            dialog.draw(result);
            dialog.display();
            sf::Event event{};
            while(dialog.pollEvent(event)){
                if(event.type == sf::Event::Closed){
                    dialog.close();
                    _window->close();
                    return;
                }
            }
        }
    }
    if(_clock.getElapsedTime().asMilliseconds() > 100){
        _clock.restart();
        nlohmann::json data;
        data["user_id"] = _client->clientId;
        data["event"] = "update_gamestate";
        _client->send(data);

        std::string received = _client->receive();
        nlohmann::json gameData = nlohmann::json::parse(received);
        gameState = GameState::deserialize(gameData);
    }
    for(int i = 0; i < _boardWidth; ++i){
        for(int j = 0; j < _boardHeight; ++j){
            Cell* cell = gameState.getCell(i, j);
            if(cell->activated){
                _cellRenderers[i * _boardWidth + j].color = sf::Color(100, 100, 100);
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

