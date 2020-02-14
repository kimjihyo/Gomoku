#include "Board.hpp"
#include <cmath>

Board:: Board(const sf::RenderWindow &window, const sf::Font &font) : BOARD_COLOR(sf::Color(202, 164, 114))
{
    sf::Vector2f boardSizeInVector(BOARD_SIZE, BOARD_SIZE);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f boardPosition(windowSize.x / 2 - BOARD_SIZE / 2, windowSize.y / 2 - BOARD_SIZE / 2);

    this->boardShape = new sf::RectangleShape(sf::Vector2f(BOARD_SIZE, BOARD_SIZE));
    this->boardShape->setFillColor(BOARD_COLOR);
    this->boardShape->setOutlineThickness(BOARD_OUTLINE_THICKNESS);
    this->boardShape->setOutlineColor(sf::Color::Black);
    this->boardShape->setPosition(boardPosition);

    this->lines = new sf::RectangleShape *[NUM_LINES * 2];
    this->indexLabels = new sf::Text *[NUM_LINES * 2];

    for (int i = 0; i < 2 * NUM_LINES; i++)
    {
        this->indexLabels[i] = new sf::Text();
        this->indexLabels[i]->setFont(font);
        // Vertical lines
        if (i < NUM_LINES)
        {
            this->lines[i] =
                new sf::RectangleShape(sf::Vector2f(LINE_THICKNESS, BOARD_SIZE - BOARD_SPACING * 2));

            this->lines[i]->setPosition(boardPosition.x + BOARD_SPACING + BOARD_SPACING * i,
                                        boardPosition.y + BOARD_SPACING);

            this->indexLabels[i]->setString(std::to_string(i + 1));
            this->indexLabels[i]->setPosition(boardPosition.x + BOARD_SPACING + BOARD_SPACING * i - TEXT_SIZE / 2,
                                              boardPosition.y - BOARD_SPACING);
        }
        // Horizontal lines
        else
        {
            this->lines[i] =
                new sf::RectangleShape(sf::Vector2f(BOARD_SIZE - BOARD_SPACING * 2 + LINE_THICKNESS, LINE_THICKNESS));
            this->lines[i]->setPosition(boardPosition.x + BOARD_SPACING,
                                        boardPosition.y + BOARD_SPACING + BOARD_SPACING * (i - 15));
            std::string label;
            label = (char)(65 + i - 15);
            this->indexLabels[i]->setString(label);
            this->indexLabels[i]->setPosition(boardPosition.x - BOARD_SPACING,
                                              boardPosition.y + BOARD_SPACING + BOARD_SPACING * (i - 15) - TEXT_SIZE / 2);
        }

        this->lines[i]->setFillColor(sf::Color::Black);
        this->indexLabels[i]->setFont(font);
        this->indexLabels[i]->setStyle(sf::Text::Bold);
        this->indexLabels[i]->setCharacterSize(TEXT_SIZE);
        this->indexLabels[i]->setFillColor(sf::Color::Black);
    }
}
Board::~Board()
{
    // Delete the plate shape buffer
    if (this->boardShape != nullptr)
    {
        delete this->boardShape;
    }

    // Delete the line shape buffers.
    for (int i = 0; i < NUM_LINES * 2; i++)
    {
        if (lines[i] != nullptr)
        {
            delete lines[i];
        }

        if (indexLabels[i] != nullptr)
        {
            delete indexLabels[i];
        }
    }
    delete[] lines;
    delete[] indexLabels;
}

sf::Vector2i Board::CalculateStoneIndexByPosition(const sf::Vector2i &position) const
{
    float predictedXPos = (position.x - this->GetBoardShape()->getPosition().x - BOARD_SPACING) / BOARD_SPACING;
    float predictedYPos = (position.y - this->GetBoardShape()->getPosition().y - BOARD_SPACING) / BOARD_SPACING;
    int indexX = roundf(predictedXPos);
    int indexY = roundf(predictedYPos);
    return sf::Vector2i(indexX, indexY);
}

sf::Vector2f Board::CalculateStonePositionToPlace(const sf::Vector2i &stoneIndex, float stoneSize) const
{
    float positionToPlaceX = stoneIndex.x * BOARD_SPACING + this->GetBoardShape()->getPosition().x - stoneSize + BOARD_SPACING;
    float positionToPlaceY = stoneIndex.y * BOARD_SPACING + this->GetBoardShape()->getPosition().y - stoneSize + BOARD_SPACING;
    return sf::Vector2f(positionToPlaceX, positionToPlaceY);
}

sf::RectangleShape *Board::GetBoardShape() const
{
    return this->boardShape;
}

sf::RectangleShape **Board::GetLineShapes() const
{
    return this->lines;
}

sf::Text **Board::GetIndexLabels() const
{
    return this->indexLabels;
}
