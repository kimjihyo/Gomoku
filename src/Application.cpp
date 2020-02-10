#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

sf::CircleShape CreateStone(const sf::Vector2f &position, int type)
{
    float stoneSize = 40.f;
    float stoneOutlineThickness = 4.f;
    sf::CircleShape stone(stoneSize);
    if (type == 1)
    {
        stone.setFillColor(sf::Color::Black);
    }
    else
    {
        stone.setFillColor(sf::Color::White);
    }
    stone.setPosition(position);
    stone.setOutlineThickness(stoneOutlineThickness);
    stone.setOutlineColor(sf::Color::Black);
    return stone;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1920), "Gomoku", sf::Style::Close);
    window.setFramerateLimit(20);
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
    int grid[15][15];
    sf::CircleShape *stoneBuffer[15][15];

    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            stoneBuffer[y][x] = nullptr;
            grid[y][x] = 0;
        }
    }

    int counter = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                float predictedXPos = (localPosition.x - board.getPosition().x) / spacing;
                float predictedYPos = (localPosition.y - board.getPosition().y) / spacing;
                int indexX = roundf(predictedXPos);
                int indexY = roundf(predictedYPos);
                float positionToPlaceX = indexX * spacing + boardPosition.x - stoneSize;
                float positionToPlaceY = indexY * spacing + boardPosition.y - stoneSize;

                std::cout << "(index) x: " << indexX << " y: " << indexY << std::endl;
                std::cout << "(position) x: " << positionToPlaceX << " y: " << positionToPlaceY << std::endl;
                std::cout << "(mouse) x: " << localPosition.x << " y: " << localPosition.y << std::endl;

                std::cout << "grid[indexY][indexX]: " << grid[indexY][indexX] << std::endl;
                if (stoneBuffer[indexY][indexY] == nullptr)
                {
                    std::cout << "stoneBuffer[indexY][indexY]: "
                              << "Not Placed" << std::endl;
                }
                else
                {
                    std::cout << "stoneBuffer[indexY][indexY]: "
                              << "Placed" << std::endl;
                }

                if (grid[indexY][indexX] == 0 && stoneBuffer[indexY][indexX] == nullptr)
                {
                    if (indexY > -1 && indexY < 15 && indexX > -1 && indexX < 15)
                    {
                        std::cout << "Stone placed!" << std::endl;
                        grid[indexY][indexX] = ++counter;
                        stoneBuffer[indexY][indexX] = new sf::CircleShape(CreateStone(sf::Vector2f(positionToPlaceX, positionToPlaceY), counter % 2));
                    }
                }
            }
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
        for (int y = 0; y < 15; y++)
        {
            for (int x = 0; x < 15; x++)
            {
                if (stoneBuffer[y][x] != nullptr)
                {
                    window.draw(*stoneBuffer[y][x]);
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