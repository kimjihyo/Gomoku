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
      shouldDisplayLabels(true)
{
    this->window = new sf::RenderWindow(sf::VideoMode(windowSizeX, windowSizeY), "Gomoku", sf::Style::Close);
    this->window->setFramerateLimit(20);
    this->font.loadFromFile("arial.ttf");
    this->board = new Board(*window, font);
    this->initStones();
    this->gomokuRule.SetStones(this->stones);
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

    sf::Vector2f textPosition(boardPosition.x, boardPosition.y + this->board->GetBoardSize() + 5.f);

    sf::Text myLabel;
    myLabel.setFont(this->font);
    myLabel.setPosition(textPosition);
    myLabel.setString("GOMOKU V.1. Lastly Updated by Jihyo Kim in Feburary 2020.");
    myLabel.setCharacterSize(24.f);
    myLabel.setColor(sf::Color::Black);
    myLabel.setStyle(sf::Text::Bold);

    Button resetButton("RESET STONES", this->font);
    resetButton.SetPosition(buttonPosition);
    resetButton.SetSize(buttonSize);

    Button labelToggleButton("TOGGLE LABELS", this->font);
    labelToggleButton.SetPosition(buttonPosition2);
    labelToggleButton.SetSize(buttonSize);

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
                        for (int i = 0; i < fiveStones.size(); i++)
                        {
                            fiveStones.at(i)->Highlight();
                        }
                    }
                }
                resetButton.OnClick(sf::Mouse::getPosition(*this->window), [this]() {
                    this->gomokuRule.Reset();
                    this->resetStones();
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
            }
            if (event.type == sf::Event::Closed)
            {
                this->window->close();
            }
        }
        this->window->clear(BACKGROUND_COLOR);
        this->drawBoard();
        this->drawStonesPlaced();
        this->drawButton(resetButton);
        this->drawButton(labelToggleButton);
        this->drawButton(undoButton);
        this->drawButton(gomokuButton);
        this->drawButton(renjuButton);
        this->window->draw(myLabel);
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

bool Gomoku::placeStone(const sf::Vector2i &localPosition)
{
    float stoneSize = this->board->GetBoardSize() / 38.f;
    sf::Vector2i stoneIndex = this->board->CalculateStoneIndexByPosition(localPosition);
    sf::Vector2f positionToPlace = this->board->CalculateStonePositionToPlace(stoneIndex, stoneSize);

    if (this->stones[stoneIndex.y][stoneIndex.x] == nullptr)
    {
        if (stoneIndex.y > -1 && stoneIndex.y < Board::NUM_LINES && stoneIndex.x > -1 && stoneIndex.x < Board::NUM_LINES)
        {
            this->stones[stoneIndex.y][stoneIndex.x] = new Stone(stoneSize, sf::Vector2f(positionToPlace.x, positionToPlace.y),
                                                                 ++counter, stoneIndex.x, stoneIndex.y);
            this->stones[stoneIndex.y][stoneIndex.x]->EnableLabel(font);
            this->stonesInOrder.push_back(this->stones[stoneIndex.y][stoneIndex.x]);
            if (!this->gomokuRule.MakeMove(stoneIndex.x, stoneIndex.y, counter % 2))
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
