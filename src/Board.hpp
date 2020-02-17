#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Board
{
private:
    sf::RectangleShape *boardShape;
    sf::RectangleShape **lines;
    sf::Text **indexLabels;
    sf::Font font;
    sf::Vector2f boardPosition;
    const sf::Color BOARD_COLOR;
    float boardSize;
    float boardOutlineThickness;
    float boardSpacing;
    float lineThickness;
    float textSize;

public:
    static constexpr unsigned short NUM_LINES = 15;

public:
    Board(const sf::RenderWindow &window, const sf::Font &font);
    ~Board();
    sf::Vector2i CalculateStoneIndexByPosition(const sf::Vector2i &position) const;
    sf::Vector2f CalculateStonePositionToPlace(const sf::Vector2i &stoneIndex, float stoneSize) const;
    sf::RectangleShape *GetBoardShape() const;
    sf::RectangleShape **GetLineShapes() const;
    sf::Text **GetIndexLabels() const;
    const sf::Vector2f &GetBoardPosition() const;
    float GetBoardSize() const;
};