#include "Board.hpp"
#include <cmath>

Board::Board(const sf::RenderWindow &window, const sf::Font &font) : BOARD_COLOR(sf::Color(202, 164, 114))
{
    sf::Vector2u windowSize = window.getSize();

    this->boardSize = windowSize.y - 400;
    this->boardOutlineThickness = this->boardSize / 250.f;
    this->lineThickness = this->boardOutlineThickness;
    this->textSize = boardSize / 15.f;
    this->boardSpacing = boardSize / (NUM_LINES + 1.f);

    unsigned int xOffset = windowSize.x / 10;
    this->boardPosition = sf::Vector2f(windowSize.x / 2 - boardSize / 2 - xOffset, windowSize.y / 2 - boardSize / 2);
    this->boardShape = new sf::RectangleShape(sf::Vector2f(boardSize, boardSize));
    this->boardShape->setFillColor(BOARD_COLOR);
    this->boardShape->setOutlineThickness(boardOutlineThickness);
    this->boardShape->setOutlineColor(sf::Color::Black);
    this->boardShape->setPosition(boardPosition);
    this->lines = new sf::RectangleShape *[NUM_LINES * 2];
    this->indexLabels = new sf::Text *[NUM_LINES * 2];

    for (int i = 0; i < 2 * NUM_LINES; i++)
    {
        this->indexLabels[i] = new sf::Text();
        this->indexLabels[i]->setFont(font);
        if (i < NUM_LINES)
        {
            this->lines[i] =
                new sf::RectangleShape(sf::Vector2f(lineThickness, boardSize - boardSpacing * 2));

            this->lines[i]->setPosition(boardPosition.x + boardSpacing + boardSpacing * i,
                                        boardPosition.y + boardSpacing);

            this->indexLabels[i]->setString(std::to_string(i + 1));
            this->indexLabels[i]->setPosition(boardPosition.x + boardSpacing + boardSpacing * i,
                                              boardPosition.y - boardSpacing);
        }
        else
        {
            this->lines[i] =
                new sf::RectangleShape(sf::Vector2f(boardSize - boardSpacing * 2 + lineThickness, lineThickness));
            this->lines[i]->setPosition(boardPosition.x + boardSpacing,
                                        boardPosition.y + boardSpacing + boardSpacing * (i - 15));
            std::string label;
            label = (char)(65 + i - 15);
            this->indexLabels[i]->setString(label);
            this->indexLabels[i]->setPosition(boardPosition.x - boardSpacing,
                                              boardPosition.y + boardSpacing + boardSpacing * (i - 15) - textSize / 2);
        }
        sf::FloatRect boundingBox = this->indexLabels[i]->getLocalBounds();
        this->indexLabels[i]->setOrigin(boundingBox.left + boundingBox.width / 2.0f,
                                        boundingBox.top + boundingBox.height / 2.0f);

        this->lines[i]->setFillColor(sf::Color::Black);
        this->indexLabels[i]->setFont(font);
        this->indexLabels[i]->setStyle(sf::Text::Bold);
        this->indexLabels[i]->setCharacterSize(textSize);
        this->indexLabels[i]->setFillColor(sf::Color::Black);
    }
    this->boardArea = sf::FloatRect(boardPosition.x, boardPosition.y, boardSize - boardSpacing, boardSize - boardSpacing);
}
Board::~Board()
{
    if (this->boardShape != nullptr)
    {
        delete this->boardShape;
    }

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
    float predictedXPos = (position.x - this->boardPosition.x - boardSpacing) / boardSpacing;
    float predictedYPos = (position.y - this->boardPosition.y - boardSpacing) / boardSpacing;
    int indexX = roundf(predictedXPos);
    int indexY = roundf(predictedYPos);
    return sf::Vector2i(indexX, indexY);
}

sf::Vector2f Board::CalculateStonePositionToPlace(const sf::Vector2i &stoneIndex, float stoneSize) const
{
    float positionToPlaceX = stoneIndex.x * boardSpacing + this->boardPosition.x - stoneSize + boardSpacing;
    float positionToPlaceY = stoneIndex.y * boardSpacing + this->boardPosition.y - stoneSize + boardSpacing;
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

const sf::Vector2f &Board::GetBoardPosition() const
{
    return this->GetBoardShape()->getPosition();
}

float Board::GetBoardSize() const
{
    return this->boardSize;
}

float Board::GetBoardSpacing() const
{
    return this->boardSpacing;
}

const sf::FloatRect& Board::GetBoardArea() const
{
    return this->boardArea;
}