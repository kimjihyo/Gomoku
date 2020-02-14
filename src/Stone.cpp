#include "Stone.hpp"

Stone::Stone(const sf::Vector2f &position, int count, unsigned int xIndex, unsigned int yIndex)
    : position(position), count(count), xIndex(xIndex), yIndex(yIndex)
{
    shapeBuffer = new sf::CircleShape(STONE_SIZE);
    labelBuffer = nullptr;
    if (count % 2 == 1)
    {
        shapeBuffer->setFillColor(sf::Color::Black);
    }
    else
    {
        shapeBuffer->setFillColor(sf::Color::White);
    }
    shapeBuffer->setPosition(position);
    shapeBuffer->setOutlineThickness(STONE_OUTLINE_THICKNESS);
    shapeBuffer->setOutlineColor(sf::Color::Black);
}
Stone::~Stone()
{
    if (shapeBuffer != nullptr)
    {
        delete shapeBuffer;
    }
    if (labelBuffer != nullptr)
    {
        delete labelBuffer;
    }
}

unsigned int Stone::getXIndex() const
{
    return this->xIndex;
}

unsigned int Stone::getYIndex() const
{
    return this->yIndex;
}

void Stone::EnableLabel(const sf::Font &font)
{
    labelBuffer = new sf::Text();
    labelBuffer->setFont(font);
    labelBuffer->setCharacterSize(LABEL_CHARACTER_SIZE);
    labelBuffer->setString(std::to_string(this->count));
    labelBuffer->setStyle(sf::Text::Bold);

    sf::FloatRect boundingBox = labelBuffer->getGlobalBounds();
    labelBuffer->setPosition(sf::Vector2f(this->position.x + STONE_SIZE / 2 - boundingBox.left,
                                          this->position.y + STONE_SIZE / 2 - boundingBox.top));

    if (this->count % 2 == 0)
    {
        labelBuffer->setColor(sf::Color::Black);
    }
}

void Stone::Highlight()
{
    if (shapeBuffer == nullptr)
    {
        return;
    }

    shapeBuffer->setOutlineColor(sf::Color::Red);
    shapeBuffer->setOutlineThickness(STONE_OUTLINE_THICKNESS * 2);
}

sf::CircleShape *Stone::GetShapeBufferPointer() const
{
    return shapeBuffer;
}

sf::Text *Stone::GetLabelBufferPointer() const
{
    return labelBuffer;
}
