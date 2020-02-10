#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1920), "Gomoku");
    window.setFramerateLimit(5);
    sf::Color backgroundColor(245, 240, 225);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f boardSize(1200.f, 1200.f);
    sf::Vector2f boardPosition(windowSize.x / 2 - boardSize.x / 2, windowSize.y / 2 - boardSize.y / 2);

    sf::Color boardColor(202, 164, 114);
    sf::RectangleShape board(boardSize);
    board.setFillColor(boardColor);
    board.setPosition(boardPosition);

    // Draw 30 lines (15 for horizontal, 15 for vertical)
    sf::RectangleShape lines[30];
    float lineThickness = 5.f;
    float spacing = boardSize.x / 14.f;

    for (int i = 0; i < 30; i++)
    {
        if (i < 15)
        {
            lines[i] = sf::RectangleShape(sf::Vector2f(lineThickness, boardSize.y));
            lines[i].setPosition(boardPosition.x + spacing * i, boardPosition.y);
        }
        else
        {
            lines[i] = sf::RectangleShape(sf::Vector2f(boardSize.x, lineThickness));
            lines[i].setPosition(boardPosition.x, boardPosition.y + spacing * (i - 15));
        }
        lines[i].setFillColor(sf::Color::Black);
    }

    float stoneSize = 40.f;
    float stoneOutlineThickness = 4.f;
    sf::CircleShape stone(stoneSize);
    stone.setFillColor(sf::Color::Black);
    stone.setPosition(sf::Vector2f(boardPosition.x - stoneSize, boardPosition.y - stoneSize));
    stone.setOutlineThickness(stoneOutlineThickness);
    stone.setOutlineColor(sf::Color::Black);

    sf::CircleShape stone2(stoneSize);
    stone2.setFillColor(sf::Color::Black);
    stone2.setPosition(sf::Vector2f(boardPosition.x + spacing - stoneSize, boardPosition.y - stoneSize));
    stone2.setOutlineThickness(stoneOutlineThickness);
    stone2.setOutlineColor(sf::Color::Black);

    sf::CircleShape stone3(stoneSize);
    stone3.setFillColor(sf::Color::White);
    stone3.setPosition(sf::Vector2f(boardPosition.x + spacing * 2 - stoneSize, boardPosition.y - stoneSize));
    stone3.setOutlineThickness(stoneOutlineThickness);
    stone3.setOutlineColor(sf::Color::Black);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(backgroundColor);
        window.draw(board);
        for (int i = 0; i < 30; i++)
        {
            window.draw(lines[i]);
        }
        window.draw(stone);
        window.draw(stone2);
        window.draw(stone3);
        window.display();
    }
    return 0;
}