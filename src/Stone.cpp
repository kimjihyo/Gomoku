#include "Stone.hpp"

Stone::Stone(float _stoneSize, const sf::Vector2f &position, int count, unsigned int xIndex, unsigned int yIndex)
    : position(position), count(count), xIndex(xIndex), yIndex(yIndex)
{
    this->stoneSize = _stoneSize;
    this->stoneOutlineThickness = this->stoneSize / 6.f;
    this->labelCharacterSize = this->stoneSize;

    shapeBuffer = new sf::CircleShape(stoneSize);
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
    shapeBuffer->setOutlineThickness(stoneOutlineThickness);
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
    labelBuffer->setCharacterSize(labelCharacterSize);
    labelBuffer->setString(std::to_string(this->count));
    labelBuffer->setStyle(sf::Text::Bold);

    sf::FloatRect boundingBox = labelBuffer->getLocalBounds();
    labelBuffer->setOrigin(boundingBox.left + boundingBox.width / 2.0f,
                           boundingBox.top + boundingBox.height / 2.0f);
    labelBuffer->setPosition(sf::Vector2f(this->position.x + this->stoneSize,
                                          this->position.y + this->stoneSize));

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
    shapeBuffer->setOutlineThickness(stoneOutlineThickness * 1.5f);
}

sf::CircleShape *Stone::GetShapeBufferPointer() const
{
    return shapeBuffer;
}

sf::Text *Stone::GetLabelBufferPointer() const
{
    return labelBuffer;
}

unsigned int Stone::GetCount() const
{
    return this->count;
}