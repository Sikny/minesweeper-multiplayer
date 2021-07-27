#ifndef CELLRENDERER_H
#define CELLRENDERER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class CellRenderer {
public:
    CellRenderer(float caseSize, sf::Vector2f position, sf::Font* font);
    void draw(sf::RenderWindow& window);
    bool hasMouseOver(sf::Vector2i mousePos);
    void hover();
    void unhover();
private:
    float posX, posY;
    sf::Text status;
    sf::RectangleShape shape;
    sf::Color color;
    sf::Color fontColor;
    float _caseSize;

};


#endif //CELLRENDERER_H
