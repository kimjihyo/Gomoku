#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Stone.hpp"
#include "Gomoku.hpp"
#include "Button.hpp"

Gomoku::Gomoku(unsigned int windowSizeX, unsigned int windowSizeY)
    : BACKGROUND_COLOR(sf::Color(245, 240, 225)), counter(0), shouldDisplayLabels(true)
{
    this->window = new sf::RenderWindow(sf::VideoMode(windowSizeX, windowSizeY), "Gomoku", sf::Style::Close);
    this->window->setFramerateLimit(20);
    this->font.loadFromFile("arial.ttf");
    this->board = new Board(*window, font);
    this->initStones();
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
    sf::Vector2f buttonPosition(boardPosition.x + Board::BOARD_SIZE + 50.f, boardPosition.y);
    sf::Vector2f buttonPosition2(buttonPosition.x, buttonPosition.y + 120.f);

    Button resetButton("RESET STONES", this->font);
    resetButton.SetPosition(buttonPosition);

    Button labelToggleButton("TOGGLE LABELS", this->font);
    labelToggleButton.SetPosition(buttonPosition2);

    while (this->window->isOpen())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
            {
                this->placeStone(sf::Mouse::getPosition(*this->window));
                resetButton.OnClick(sf::Mouse::getPosition(*this->window), [this]() {
                    this->resetStones();
                });
                labelToggleButton.OnClick(sf::Mouse::getPosition(*this->window), [this]() {
                    this->shouldDisplayLabels = !this->shouldDisplayLabels;
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
        this->window->draw(resetButton.GetButtonShape());
        this->window->draw(resetButton.GetLabelShape());
        this->window->draw(labelToggleButton.GetButtonShape());
        this->window->draw(labelToggleButton.GetLabelShape());
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

bool Gomoku::placeStone(const sf::Vector2i &localPosition)
{
    sf::Vector2i stoneIndex = this->board->CalculateStoneIndexByPosition(localPosition);
    sf::Vector2f positionToPlace = this->board->CalculateStonePositionToPlace(stoneIndex, Stone::STONE_SIZE);

    if (this->stones[stoneIndex.y][stoneIndex.x] == nullptr)
    {
        if (stoneIndex.y > -1 && stoneIndex.y < Board::NUM_LINES && stoneIndex.x > -1 && stoneIndex.x < Board::NUM_LINES)
        {
            this->stones[stoneIndex.y][stoneIndex.x] = new Stone(sf::Vector2f(positionToPlace.x, positionToPlace.y),
                                                                 ++counter, stoneIndex.x, stoneIndex.y);
            this->stones[stoneIndex.y][stoneIndex.x]->EnableLabel(font);
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
