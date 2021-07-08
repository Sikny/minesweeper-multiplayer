#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>

class Case
{
    public:
        Case();
        Case(float x, float y, int indX, int indY, float caseSize);
        void setFont(sf::Font*);
        int getX();
        int getY();
        void draw(sf::RenderWindow&);
        void hover();
        std::string select(Case* board);
        void unhover();
        bool hasMouseOver(sf::Vector2i mousePos);
        void setBomb();
        bool hasBomb();
        bool isReturned();
        std::string getStatus();
        int testCase(Case* board);
        void setLimits(int min, int max);

    private:
        float posX, posY;
        int indX, indY;
        int min, max;
        float caseSize;
        sf::Color color;
        sf::Color fontColor;
        bool bomb, returned;
        sf::Text status;
        sf::RectangleShape shape;
        sf::Font* font;
};

#endif // CASE_H
