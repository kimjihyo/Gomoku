#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1920), "Gomoku");
    window.setFramerateLimit(10);
    sf::Color backgroundColor(245, 240, 225);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f boardSize(1200.f, 1200.f);
    sf::Vector2f boardPosition(windowSize.x / 2 - boardSize.x / 2, windowSize.y / 2 - boardSize.y / 2);

    sf::RectangleShape board(boardSize);
    board.setFillColor(sf::Color(222, 218, 206));
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

    window.draw(board);

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
        window.display();
    }
    return 0;
}