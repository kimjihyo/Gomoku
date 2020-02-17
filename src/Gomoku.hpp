#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Stone.hpp"

class Gomoku
{
private:
    sf::RenderWindow *window;
    sf::Font font;
    const sf::Color BACKGROUND_COLOR;

    Board *board;
    Stone *stones[Board::NUM_LINES][Board::NUM_LINES];
    
    int counter;

public:
    Gomoku(unsigned int windowSizeX, unsigned int windowSizeY);
    ~Gomoku();
    void StartGame();

private:
    void initStones();
    bool placeStone(const sf::Vector2i& position);
    void drawBoard();
    void drawStonesPlaced();
};