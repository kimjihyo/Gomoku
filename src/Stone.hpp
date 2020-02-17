#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Stone
{
private:
    sf::CircleShape *shapeBuffer;
    sf::Text *labelBuffer;
    sf::Vector2f position;
    unsigned int count;
    unsigned int xIndex;
    unsigned int yIndex;
    float stoneSize;
    float stoneOutlineThickness;
    float labelCharacterSize;

public:
    Stone(float _stoneSize, const sf::Vector2f &position, int count, unsigned int xIndex, unsigned int yIndex);
    ~Stone();
    unsigned int getXIndex() const;
    unsigned int getYIndex() const;
    unsigned int GetCount() const;
    void EnableLabel(const sf::Font &font);
    void Highlight();
    sf::CircleShape *GetShapeBufferPointer() const;
    sf::Text *GetLabelBufferPointer() const;
};