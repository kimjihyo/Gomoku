#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Stone.hpp"
#include "Gomoku.hpp"
#include "Button.hpp"

Gomoku::Gomoku(unsigned int windowSizeX, unsigned int windowSizeY)
    : BACKGROUND_COLOR(sf::Color(245, 240, 225)),
      counter(0),
      shouldDisplayLabels(true),
      shouldEnableIndicator(true)
{
    this->window = new sf::RenderWindow(sf::VideoMode(windowSizeX, windowSizeY), "Gomoku", sf::Style::Close);
    this->window->setFramerateLimit(20);
    this->font.loadFromFile("font.ttf");
    this->board = new Board(*window, font);
    this->initStones();
    this->gomokuRule.SetStones(this->stones);
    const sf::Vector2i &tempPosition = sf::Mouse::getPosition(*this->window);
    this->cachedMousePositionX = tempPosition.x;
    this->cachedMousePositionY = tempPosition.y;
    this->stoneSize = this->board->GetBoardSize() / 38.f;

    this->indicator.setFillColor(sf::Color::Black);
    this->indicator.setSize(sf::Vector2f(this->stoneSize * 1.2f, this->stoneSize * 1.2f));
    this->indicator.setOutlineColor(sf::Color::Black);
    this->indicator.setOutlineThickness(3.f);
    this->reader.SetFilepath("./move.txt");
}

Gomoku::~Gomoku()
{

    for (int y = 0; y < Board::NUM_LINES; y++)
    {
        for (int x = 0; x < Board::NUM_LINES; x++)
        {
            if (this->stones[y][x] != nullptr)
            {
                delete stones[y][x];
            }
        }
    }
    delete window;
    delete board;
}

void Gomoku::StartGame()
{
    const sf::Vector2f &boardPosition = this->board->GetBoardPosition();
    sf::Vector2f buttonSize(this->board->GetBoardSize() / 4.f, this->board->GetBoardSize() / 12.f);

    sf::Vector2f buttonPosition(boardPosition.x + this->board->GetBoardSize() + buttonSize.y, boardPosition.y);
    sf::Vector2f buttonPosition2(buttonPosition.x, buttonPosition.y + buttonSize.y * 1.5f);
    sf::Vector2f buttonPosition3(buttonPosition.x, buttonPosition2.y + buttonSize.y * 1.5f);
    sf::Vector2f gomokuButtonPosition(buttonPosition.x, buttonPosition3.y + buttonSize.y * 1.5f);
    sf::Vector2f renjuButtonPosition(buttonPosition.x, gomokuButtonPosition.y + buttonSize.y * 1.5f);
    sf::Vector2f readFromTextFileButtonPosition(buttonPosition.x, renjuButtonPosition.y + buttonSize.y * 1.5f);

    sf::Vector2f textPosition(boardPosition.x, boardPosition.y + this->board->GetBoardSize() + 5.f);

    sf::Text myLabel;
    myLabel.setFont(this->font);
    myLabel.setPosition(textPosition);
    myLabel.setString("GOMOKU V.1. Lastly Updated by Jihyo Kim in Feburary 2020.\nSource code is available at this link https://github.com/kimjihyo/Gomoku.");
    myLabel.setCharacterSize(48.f);
    myLabel.setColor(sf::Color::Black);
    myLabel.setStyle(sf::Text::Bold);

    Button resetButton("RESET STONES", this->font);
    resetButton.SetPosition(buttonPosition);
    resetButton.SetSize(buttonSize);

    Button labelToggleButton("TOGGLE LABELS", this->font);
    labelToggleButton.SetPosition(buttonPosition2);
    labelToggleButton.SetSize(buttonSize);
    labelToggleButton.MakeButtonToggle();
    labelToggleButton.Toggle();

    Button undoButton("UNDO", this->font);
    undoButton.SetPosition(buttonPosition3);
    undoButton.SetSize(buttonSize);

    Button gomokuButton("GOMOKU", this->font);
    gomokuButton.SetPosition(gomokuButtonPosition);
    gomokuButton.SetSize(buttonSize);
    gomokuButton.MakeButtonToggle();

    Button renjuButton("RENJU", this->font);
    renjuButton.SetPosition(renjuButtonPosition);
    renjuButton.SetSize(buttonSize);
    renjuButton.MakeButtonToggle();
    renjuButton.Toggle();

    Button readFromTextFileButton("READ FROM TEXT FILE", this->font);
    // renjuButton.SetPosition(readFromTextFileButtonPosition);
    // renjuButton.SetSize(buttonSize);

    const std::vector<Stone *> &fiveStones = this->gomokuRule.GetFiveStonesInRow();

    while (this->window->isOpen())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
            {
                if (!this->gomokuRule.GetIsGameEnded())
                {
                    this->placeStone(sf::Mouse::getPosition(*this->window));
                    if (this->gomokuRule.GetIsGameEnded())
                    {
                        std::cout << "Game has ended!" << std::endl;
                        for (int i = 0; i < fiveStones.size(); i++)
                        {
                            fiveStones.at(i)->Highlight();
                        }
                        this->shouldEnableIndicator = false;
                    }
                }
                resetButton.OnClick(sf::Mouse::getPosition(*this->window), [this]() {
                    this->gomokuRule.Reset();
                    this->resetStones();
                    this->shouldEnableIndicator = true;
                });
                labelToggleButton.OnClick(sf::Mouse::getPosition(*this->window), [this]() {
                    this->shouldDisplayLabels = !this->shouldDisplayLabels;
                });
                undoButton.OnClick(sf::Mouse::getPosition(*this->window), [this]() {
                    this->undoLastStone();
                });
                gomokuButton.OnClick(sf::Mouse::getPosition(*this->window), [this, &renjuButton]() {
                    if (this->gomokuRule.GetRuleType() != GOMOKU)
                    {
                        std::cout << "The game rule has been changed to GOMOKU" << std::endl;
                        this->gomokuRule.SetRuleType(GOMOKU);
                        renjuButton.Toggle();
                    }
                });
                renjuButton.OnClick(sf::Mouse::getPosition(*this->window), [this, &gomokuButton]() {
                    if (this->gomokuRule.GetRuleType() != RENJU)
                    {
                        std::cout << "The game rule has been changed to RENJU" << std::endl;
                        this->gomokuRule.SetRuleType(RENJU);
                        gomokuButton.Toggle();
                    }
                });
                readFromTextFileButton.OnClick(sf::Mouse::getPosition(*this->window), [this]() {
                    std::cout << "read from text file button clicked!" << std::endl;
                    int matrix[15][15];
                    this->reader.GetIntegerMatrix(matrix);
                    this->gomokuRule.Reset();
                    this->resetStones();
                    this->placeStonesFromIntegerMatrix(matrix);
                });
            }
            if (event.type == sf::Event::Closed)
            {
                this->window->close();
            }
        }
        this->window->clear(sf::Color::White);
        this->drawBoard();
        this->drawButton(resetButton);
        this->drawButton(labelToggleButton);
        this->drawButton(undoButton);
        this->drawButton(gomokuButton);
        this->drawButton(renjuButton);
        this->drawButton(readFromTextFileButton);
        if (this->shouldEnableIndicator)
        {
            this->drawIndicator(sf::Mouse::getPosition(*this->window));
        }
        this->window->draw(myLabel);
        this->drawStonesPlaced();
        this->window->display();
    }
}

void Gomoku::initStones()
{
    for (int y = 0; y < Board::NUM_LINES; y++)
    {
        for (int x = 0; x < Board::NUM_LINES; x++)
        {
            this->stones[y][x] = nullptr;
        }
    }
}

void Gomoku::drawBoard()
{
    this->window->draw(*this->board->GetBoardShape());
    for (int i = 0; i < 30; i++)
    {
        this->window->draw(*this->board->GetLineShapes()[i]);
        this->window->draw(*this->board->GetIndexLabels()[i]);
    }
}

void Gomoku::drawStonesPlaced()
{
    for (int y = 0; y < Board::NUM_LINES; y++)
    {
        for (int x = 0; x < Board::NUM_LINES; x++)
        {
            if (this->stones[y][x] != nullptr)
            {
                this->window->draw(*this->stones[y][x]->GetShapeBufferPointer());
                if (this->shouldDisplayLabels)
                {
                    this->window->draw(*this->stones[y][x]->GetLabelBufferPointer());
                }
            }
        }
    }
}

void Gomoku::drawButton(const Button &button)
{
    this->window->draw(button.GetButtonShape());
    this->window->draw(button.GetLabelShape());
}

void Gomoku::drawIndicator(const sf::Vector2i &localPosition)
{
    if (!this->board->GetBoardArea().contains(sf::Vector2f(localPosition.x, localPosition.y)))
    {
        return;
    }

    float indicatorSize = this->indicator.getSize().x;
    if (abs(cachedMousePositionX - localPosition.x) < this->stoneSize &&
        abs(cachedMousePositionY - localPosition.y) < this->stoneSize)
    {
        this->window->draw(this->indicator);
        return;
    }
    else
    {
        cachedMousePositionX = localPosition.x;
        cachedMousePositionY = localPosition.y;
    }

    sf::Vector2i index = this->board->CalculateStoneIndexByPosition(localPosition);
    sf::Vector2f positionOfIndicator = this->board->CalculateStonePositionToPlace(index, indicatorSize);
    if (index.x > -1 && index.x < Board::NUM_LINES && index.y > -1 && index.y < Board::NUM_LINES)
    {
        this->indicator.setPosition(sf::Vector2f(positionOfIndicator.x + indicatorSize / 2, positionOfIndicator.y + indicatorSize / 2));
        this->window->draw(this->indicator);
    }
}

bool Gomoku::placeStone(const sf::Vector2i &localPosition)
{
    sf::Vector2i stoneIndex = this->board->CalculateStoneIndexByPosition(localPosition);
    sf::Vector2f positionToPlace = this->board->CalculateStonePositionToPlace(stoneIndex, this->stoneSize);

    if (this->stones[stoneIndex.y][stoneIndex.x] == nullptr)
    {
        if (stoneIndex.y > -1 && stoneIndex.y < Board::NUM_LINES && stoneIndex.x > -1 && stoneIndex.x < Board::NUM_LINES)
        {
            this->stones[stoneIndex.y][stoneIndex.x] = new Stone(this->stoneSize, sf::Vector2f(positionToPlace.x, positionToPlace.y),
                                                                 ++counter, stoneIndex.x, stoneIndex.y);
            this->stones[stoneIndex.y][stoneIndex.x]->EnableLabel(font);
            this->stonesInOrder.push_back(this->stones[stoneIndex.y][stoneIndex.x]);
            if (this->gomokuRule.MakeMove(stoneIndex.x, stoneIndex.y, counter % 2))
            {
                this->indicator.setFillColor(this->counter % 2 == 0 ? sf::Color::Black : sf::Color::White);
            }
            else
            {
                this->undoLastStone();
            }
            return true;
        }
    }
    return false;
}

void Gomoku::resetStones()
{
    for (int y = 0; y < Board::NUM_LINES; y++)
    {
        for (int x = 0; x < Board::NUM_LINES; x++)
        {
            if (this->stones[y][x] != nullptr)
            {
                delete stones[y][x];
                stones[y][x] = nullptr;
            }
        }
    }
    this->counter = 0;
}

void Gomoku::undoLastStone()
{
    if (!stonesInOrder.empty())
    {
        Stone *prevStone = stonesInOrder.back();
        stonesInOrder.pop_back();
        unsigned int x = prevStone->getXIndex();
        unsigned int y = prevStone->getYIndex();
        delete this->stones[y][x];
        this->stones[y][x] = nullptr;
        this->counter--;
    }
}

void Gomoku::placeStonesFromIntegerMatrix(int (*matrix)[Board::NUM_LINES])
{
    for (int y = 0; y < Board::NUM_LINES; y++)
    {
        for (int x = 0; x < Board::NUM_LINES; x++)
        {
            if (matrix[y][x] != 0)
            {
                sf::Vector2f positionToPlace = this->board->CalculateStonePositionToPlace(sf::Vector2i(x, y), this->stoneSize);
                this->stones[y][x] = new Stone(this->stoneSize, sf::Vector2f(positionToPlace.x, positionToPlace.y),
                                               ++counter, x, y);
                this->stones[y][x]->EnableLabel(font);
                this->stonesInOrder.push_back(this->stones[y][x]);
            }
        }
    }
}

void Gomoku::exportCurrentKiboToIntegerMatrix(int (*matrix)[Board::NUM_LINES]) const
{
    for (int y = 0; y < Board::NUM_LINES; y++)
    {
        for (int x = 0; x < Board::NUM_LINES; x++)
        {
            if (stones[y][x] != nullptr)
            {
                matrix[y][x] = stones[y][x]->GetCount();
            }
            else
            {
                matrix[y][x] = 0;
            }
        }
    }
}
