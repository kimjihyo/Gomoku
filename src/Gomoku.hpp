#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Board.hpp"
#include "Stone.hpp"
#include "Button.hpp"
#include "GomokuRule.hpp"
#include "GomokuReader.hpp"

class Gomoku
{
private:
    sf::RenderWindow *window;
    sf::Font font;
    const sf::Color BACKGROUND_COLOR;

    Board *board;
    Stone *stones[Board::NUM_LINES][Board::NUM_LINES];
    GomokuRule gomokuRule;
    GomokuReader reader;
    std::vector<Stone*> stonesInOrder;
    sf::RectangleShape indicator;
    
    int counter;
    bool shouldDisplayLabels;
    bool shouldEnableIndicator;
    bool isMouseInsideBoard;

    int cachedMousePositionX;
    int cachedMousePositionY;

    float stoneSize;

public:
    Gomoku(unsigned int windowSizeX, unsigned int windowSizeY);
    ~Gomoku();
    void StartGame();

private:
    void initStones();
    bool placeStone();
    void drawBoard();
    void drawStonesPlaced();
    void drawButton(const Button& button);
    void resetStones();
    void undoLastStone();
    void drawIndicator(const sf::Vector2i& position);
    void placeStonesFromIntegerMatrix(int (*matrix)[Board::NUM_LINES]);
    void exportCurrentKiboToIntegerMatrix(int (*matrix)[Board::NUM_LINES]) const;
};