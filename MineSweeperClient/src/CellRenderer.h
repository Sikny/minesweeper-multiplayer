#ifndef CELLRENDERER_H
#define CELLRENDERER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class CellRenderer {
public:
    CellRenderer(float caseSize, sf::Vector2f position, sf::Font* font);
    void draw(sf::RenderWindow& window);
private:
    sf::Text status;
    sf::RectangleShape shape;
    sf::Color color;
    sf::Color fontColor;
};


#endif //CELLRENDERER_H
