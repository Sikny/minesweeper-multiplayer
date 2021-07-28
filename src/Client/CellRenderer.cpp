#include "CellRenderer.h"

CellRenderer::CellRenderer(float caseSize, sf::Vector2f position, sf::Font* font)
        : color(sf::Color::White), fontColor(sf::Color::Blue), _caseSize(caseSize){
    shape = sf::RectangleShape(sf::Vector2f(caseSize, caseSize));
    status.setCharacterSize(120);
    status.setScale(0.25, 0.25);
    shape.setPosition(position.x, position.y);
    status.setPosition(position.x + caseSize/4, position.y - caseSize/8);
    status.setFont(*font);
    posX = position.x;
    posY = position.y;
}

void CellRenderer::draw(sf::RenderWindow &window) {
    shape.setFillColor(color);
    status.setFillColor(fontColor);
    window.draw(shape);
    window.draw(status);
}

void CellRenderer::hover() {
    color = sf::Color(150, 150, 150);
}

void CellRenderer::unhover() {
    color = sf::Color::White;
}

bool CellRenderer::hasMouseOver(sf::Vector2i mousePos) const {
    return (mousePos.x >= posX && mousePos.y >= posY
        && mousePos.x <= posX+_caseSize && mousePos.y <= posY+_caseSize);
}

void CellRenderer::setStatus(int _status) {
    status.setString(std::to_string(_status));
    switch(_status){
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
