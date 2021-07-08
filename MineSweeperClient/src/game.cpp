#include "game.h"

Game::Game(std::string difficulty, int boardSize_p, int nBombs_p) : cellSize(30.0f),
boardSize(boardSize_p), nBombs(nBombs_p), difficulty_str(difficulty),
window(sf::VideoMode(cellSize*boardSize+cellSize*2, cellSize*boardSize+cellSize*2)
       , "Minesweeper - " + difficulty_str){
    std::cout << "Difficulty set to: " << difficulty_str << std::endl;
    font = new sf::Font();
    font->loadFromFile("resources/arial.ttf");
    std::cout << "Building board..." << std::endl;
    board = new Case[boardSize*boardSize];
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            board[i*boardSize+j] = Case(i*(cellSize+1)+cellSize-boardSize/2, j*(cellSize+1)+cellSize-boardSize/2, i, j, cellSize);
            board[i*boardSize+j].setFont(font);
            board[i*boardSize+j].setLimits(0, boardSize-1);
        }
    }
    std::cout << "Setting bombs..." << std::endl;
    int plantedBombs = 0;
    std::srand(std::time(nullptr));
    while(plantedBombs < nBombs){
        int selectedCase = 0;
        do{
            selectedCase = (rand() % static_cast<int>(boardSize*boardSize));
        } while(board[selectedCase].hasBomb());
        plantedBombs++;
        board[selectedCase].setBomb();
    }
}

void Game::run(){
    while(window.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::processEvents(){
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if(event.type == sf::Event::MouseButtonPressed){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for(unsigned short i = 0; i < boardSize*boardSize; i++){
                if(board[i].hasMouseOver(mousePos)){
                    std::string status = board[i].select(board);
                    if(!status.empty()) {
                        std::cout << status << std::endl;
                        std::exit(EXIT_SUCCESS);
                    }
                }
            }
        }
        else if(event.type == sf::Event::MouseMoved){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for(unsigned short i = 0; i < boardSize*boardSize; i++){
                if(board[i].hasMouseOver(mousePos)){
                    if(event.type == sf::Event::MouseMoved) board[i].hover();
                }
                else board[i].unhover();
            }
        }
    }
}

void Game::update(){
    if(hasWon()){
        std::cout << "You win" << std::endl;
        std::exit(EXIT_SUCCESS);
    }
}

void Game::render(){
    window.clear();
    for(int i = 0; i < boardSize*boardSize; i++){
        board[i].draw(window);
    }
    window.display();
}

bool Game::hasWon(){
    int solvedCases = 0;
    for(int i = 0; i < boardSize*boardSize; i++){
        if(board[i].isReturned()) solvedCases++;
    }
    return (boardSize*boardSize-solvedCases) == nBombs;
}
