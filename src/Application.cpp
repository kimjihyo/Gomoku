#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

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
    static constexpr float LABEL_CHARACTER_SIZE = 40.f;

public:
    Stone(const sf::Vector2f &position, int count, unsigned int xIndex, unsigned int yIndex)
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
    ~Stone()
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

    unsigned int getXIndex() const
    {
        return this->xIndex;
    }

    unsigned int getYIndex() const
    {
        return this->yIndex;
    }

    void EnableLabel(const sf::Font &font)
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

    void Highlight()
    {
        if (shapeBuffer == nullptr)
        {
            return;
        }

        shapeBuffer->setOutlineColor(sf::Color::Red);
        shapeBuffer->setOutlineThickness(STONE_OUTLINE_THICKNESS * 2);
    }

    sf::CircleShape *GetShapeBufferPointer() const
    {
        return shapeBuffer;
    }

    sf::Text *GetLabelBufferPointer() const
    {
        return labelBuffer;
    }
};

class Board
{
private:
    sf::RectangleShape *boardShape;
    sf::RectangleShape **lines;
    sf::Text **indexLabels;
    sf::Font font;
    const sf::Color BOARD_COLOR;

public:
    static constexpr unsigned short NUM_LINES = 15;
    static constexpr float BOARD_SIZE = 1200.f;
    static constexpr float BOARD_OUTLINE_THICKNESS = 4.f;
    static constexpr float BOARD_SPACING = BOARD_SIZE / (NUM_LINES + 1.f);
    static constexpr float LINE_THICKNESS = 4.f;
    static constexpr float TEXT_SIZE = 35.f;

public:
    Board(const sf::RenderWindow &window, const sf::Font &font) : BOARD_COLOR(sf::Color(202, 164, 114))
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
    ~Board()
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

    sf::Vector2i CalculateStoneIndexByPosition(const sf::Vector2i &position) const
    {
        float predictedXPos = (position.x - this->GetBoardShape()->getPosition().x - BOARD_SPACING) / BOARD_SPACING;
        float predictedYPos = (position.y - this->GetBoardShape()->getPosition().y - BOARD_SPACING) / BOARD_SPACING;
        int indexX = roundf(predictedXPos);
        int indexY = roundf(predictedYPos);
        return sf::Vector2i(indexX, indexY);
    }

    sf::Vector2f CalculateStonePositionToPlace(const sf::Vector2i &stoneIndex, float stoneSize) const
    {
        float positionToPlaceX = stoneIndex.x * BOARD_SPACING + this->GetBoardShape()->getPosition().x - stoneSize + BOARD_SPACING;
        float positionToPlaceY = stoneIndex.y * BOARD_SPACING + this->GetBoardShape()->getPosition().y - stoneSize + BOARD_SPACING;
        return sf::Vector2f(positionToPlaceX, positionToPlaceY);
    }

    sf::RectangleShape *GetBoardShape() const
    {
        return this->boardShape;
    }

    sf::RectangleShape **GetLineShapes() const
    {
        return this->lines;
    }

    sf::Text **GetIndexLabels() const
    {
        return this->indexLabels;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1920), "Gomoku", sf::Style::Close);
    window.setFramerateLimit(20);
    sf::Color backgroundColor(245, 240, 225);
    sf::Font font;

    if (!font.loadFromFile("arial.ttf"))
    {
        return -1;
    }
    
    Board board(window, font);
    Stone *stoneBuffer[15][15];
    int counter = 0;

    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            stoneBuffer[y][x] = nullptr;
        }
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                sf::Vector2i stoneIndex = board.CalculateStoneIndexByPosition(localPosition);
                sf::Vector2f positionToPlace = board.CalculateStonePositionToPlace(stoneIndex, Stone::STONE_SIZE);

                if (stoneBuffer[stoneIndex.y][stoneIndex.x] == nullptr)
                {
                    if (stoneIndex.y > -1 && stoneIndex.y < 15 && stoneIndex.x > -1 && stoneIndex.x < 15)
                    {
                        std::cout << "Stone placed!" << std::endl;
                        stoneBuffer[stoneIndex.y][stoneIndex.x] = new Stone(sf::Vector2f(positionToPlace.x, positionToPlace.y),
                                                                ++counter, stoneIndex.x, stoneIndex.y);
                        stoneBuffer[stoneIndex.y][stoneIndex.x]->EnableLabel(font);
                    }
                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(backgroundColor);
        window.draw(*board.GetBoardShape());
        for (int i = 0; i < 30; i++)
        {
            window.draw(*board.GetLineShapes()[i]);
            window.draw(*board.GetIndexLabels()[i]);
        }
        for (int y = 0; y < 15; y++)
        {
            for (int x = 0; x < 15; x++)
            {
                if (stoneBuffer[y][x] != nullptr)
                {
                    window.draw(*stoneBuffer[y][x]->GetShapeBufferPointer());
                    window.draw(*stoneBuffer[y][x]->GetLabelBufferPointer());
                }
            }
        }

        window.display();
    }

    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            if (stoneBuffer[y][x] != nullptr)
            {
                delete stoneBuffer[y][x];
            }
        }
    }

    return 0;
}