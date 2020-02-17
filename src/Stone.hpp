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

public:
    static constexpr float STONE_SIZE = 32.5f;
    static constexpr float STONE_OUTLINE_THICKNESS = 4.f;
    static constexpr float LABEL_CHARACTER_SIZE = 35.f;

public:
    Stone(const sf::Vector2f &position, int count, unsigned int xIndex, unsigned int yIndex);
    ~Stone();
    unsigned int getXIndex() const;
    unsigned int getYIndex() const;
    unsigned int GetCount() const;
    void EnableLabel(const sf::Font &font);
    void Highlight();
    sf::CircleShape *GetShapeBufferPointer() const;
    sf::Text *GetLabelBufferPointer() const;

};