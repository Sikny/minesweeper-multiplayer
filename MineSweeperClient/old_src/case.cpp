#include "case.h"

Case::Case(){}

Case::Case(float x, float y, int indX_p, int indY_p, float caseSize_p)
: posX(x), posY(y), indX(indX_p), indY(indY_p), caseSize(caseSize_p),
color(sf::Color::White), fontColor(sf::Color::Blue), bomb(false),
returned(false), status(sf::Text()){
    shape = sf::RectangleShape(sf::Vector2f(caseSize, caseSize));
    shape.setPosition(posX, posY);
    status.setCharacterSize(120);
    status.setScale(0.25, 0.25);
    status.setPosition(posX+caseSize/4, posY-caseSize/8);
}

void Case::setFont(sf::Font* font_p){
    font = font_p;
    status.setFont(*font);
}

int Case::getX(){
    return indX;
}
int Case::getY(){
    return indX;
}

void Case::draw(sf::RenderWindow& window){
    shape.setFillColor(color);
    status.setFillColor(fontColor);
    window.draw(shape);
    window.draw(status);
}

void Case::hover(){
    if(!returned)
        color = sf::Color(150, 150, 150);
}

std::string Case::select(Case* board){
    returned = true;
    color = sf::Color(100, 100, 100);
    if(bomb) return "You lose";
    else {
        // Counting bombs around
        int nBombs = 0;
        for(short i = indX-1; i <= indX+1; i++){
            for(short j = indY-1; j <= indY+1; j++){
                if(i >= min && i <= max && j >= min && j <= max){
                    if(board[i*(max+1)+j].hasBomb())
                        nBombs++;
                }
            }
        }
        if(nBombs == 0) {
            for(short i = indX-1; i <= indX+1; i++){
                for(short j = indY-1; j <= indY+1; j++){
                    if(i >= min && i <= max && j >= min && j <= max){
                        if(!board[i*(max+1)+j].returned)
                            board[i*(max+1)+j].select(board);
                    }
                }
            }
        } else {
            status.setString(std::to_string(nBombs));
            switch(nBombs){
                case 1:
                    fontColor = sf::Color::Blue;
                    break;
                case 2:
                    fontColor = sf::Color::Green;
                    break;
                case 3:
                    fontColor = sf::Color::Red;
                    break;
                case 4:
                    fontColor = sf::Color(0, 0, 132);
                    break;
                case 5:
                    fontColor = sf::Color(132, 0, 0);
                    break;
                case 6:
                    fontColor = sf::Color::Cyan;
                    break;
                default:
                    fontColor = sf::Color(64, 0, 64);
            }
        }
        return "";
    }
}

void Case::unhover(){
    if(!returned)
        color = sf::Color::White;
}

bool Case::hasMouseOver(sf::Vector2i mousePos){
    return (mousePos.x >= posX && mousePos.y >= posY
        && mousePos.x <= posX+caseSize && mousePos.y <= posY+caseSize);
}

void Case::setBomb(){
    bomb = true;
}

bool Case::hasBomb(){
    return bomb;
}

std::string Case::getStatus(){
    return status.getString().toAnsiString();
}

void Case::setLimits(int min_p, int max_p){
    min = min_p;
    max = max_p;
}

bool Case::isReturned(){
    return returned;
}
