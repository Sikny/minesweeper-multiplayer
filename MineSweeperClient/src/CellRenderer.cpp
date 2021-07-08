#include "CellRenderer.h"

CellRenderer::CellRenderer(float caseSize, sf::Vector2f position, sf::Font* font) {
    shape = sf::RectangleShape(sf::Vector2f(caseSize, caseSize));
    status.setCharacterSize(120);
    status.setScale(0.25, 0.25);
    shape.setPosition(position.x, position.y);
    status.setPosition(position.x + caseSize/4, position.y - caseSize/8);
    status.setFont(*font);
}

void CellRenderer::draw(sf::RenderWindow &window) {
    shape.setFillColor(color);
    status.setFillColor(fontColor);
    window.draw(shape);
    window.draw(status);
}