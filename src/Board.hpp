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
    const sf::Color BOARD_COLOR;

public:
    static constexpr unsigned short NUM_LINES = 15;
    static constexpr float BOARD_SIZE = 1200.f;
    static constexpr float BOARD_OUTLINE_THICKNESS = 4.f;
    static constexpr float BOARD_SPACING = BOARD_SIZE / (NUM_LINES + 1.f);
    static constexpr float LINE_THICKNESS = 4.f;
    static constexpr float TEXT_SIZE = 35.f;

public:
    Board(const sf::RenderWindow &window, const sf::Font &font);
    ~Board();
    sf::Vector2i CalculateStoneIndexByPosition(const sf::Vector2i &position) const;
    sf::Vector2f CalculateStonePositionToPlace(const sf::Vector2i &stoneIndex, float stoneSize) const;
    sf::RectangleShape *GetBoardShape() const;
    sf::RectangleShape **GetLineShapes() const;
    sf::Text **GetIndexLabels() const;
};