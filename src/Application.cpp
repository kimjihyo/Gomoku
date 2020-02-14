#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Stone.hpp"
#include "Board.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1920), "Gomoku", sf::Style::Close);
    window.setFramerateLimit(20);
    sf::Color backgroundColor(245, 240, 225);
    sf::Font font;

    if (!font.loadFromFile("arial.ttf"))
    {
        return -1;
    }
    
    Board board(window, font);
    Stone *stoneBuffer[15][15];
    int counter = 0;

    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            stoneBuffer[y][x] = nullptr;
        }
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                sf::Vector2i stoneIndex = board.CalculateStoneIndexByPosition(localPosition);
                sf::Vector2f positionToPlace = board.CalculateStonePositionToPlace(stoneIndex, Stone::STONE_SIZE);

                if (stoneBuffer[stoneIndex.y][stoneIndex.x] == nullptr)
                {
                    if (stoneIndex.y > -1 && stoneIndex.y < 15 && stoneIndex.x > -1 && stoneIndex.x < 15)
                    {
                        std::cout << "Stone placed!" << std::endl;
                        stoneBuffer[stoneIndex.y][stoneIndex.x] = new Stone(sf::Vector2f(positionToPlace.x, positionToPlace.y),
                                                                ++counter, stoneIndex.x, stoneIndex.y);
                        stoneBuffer[stoneIndex.y][stoneIndex.x]->EnableLabel(font);
                    }
                }
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(backgroundColor);
        window.draw(*board.GetBoardShape());
        for (int i = 0; i < 30; i++)
        {
            window.draw(*board.GetLineShapes()[i]);
            window.draw(*board.GetIndexLabels()[i]);
        }
        for (int y = 0; y < 15; y++)
        {
            for (int x = 0; x < 15; x++)
            {
                if (stoneBuffer[y][x] != nullptr)
                {
                    window.draw(*stoneBuffer[y][x]->GetShapeBufferPointer());
                    window.draw(*stoneBuffer[y][x]->GetLabelBufferPointer());
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