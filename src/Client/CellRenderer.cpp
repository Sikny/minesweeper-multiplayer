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

bool CellRenderer::hasMouseOver(sf::Vector2i mousePos) {
    return (mousePos.x >= posX && mousePos.y >= posY
        && mousePos.x <= posX+_caseSize && mousePos.y <= posY+_caseSize);
}
