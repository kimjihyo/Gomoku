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
      shouldDisplayLabels(true),
      shouldEnableIndicator(true)
{
    this->window = new sf::RenderWindow(sf::VideoMode(windowSizeX, windowSizeY), "Gomoku", sf::Style::Close);
    this->window->setFramerateLimit(20);
    this->font.loadFromFile("font.ttf");
    this->board = new Board(*window, font);
    this->initStones();
    this->gomokuRule.SetStones(this->stones);
    const sf::Vector2i &tempPosition = sf::Mouse::getPosition(*this->window);
    this->cachedMousePositionX = tempPosition.x;
    this->cachedMousePositionY = tempPosition.y;
    this->stoneSize = this->board->GetBoardSize() / 38.f;

    this->indicator.setFillColor(sf::Color::Black);
    this->indicator.setSize(sf::Vector2f(this->stoneSize * 1.2f, this->stoneSize * 1.2f));
    this->indicator.setOutlineColor(sf::Color::Black);
    this->indicator.setOutlineThickness(3.f);
    this->reader.SetFilepath("./move.txt");
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

    for (Button* button : this->buttons)
    {
        delete button;
    }

    delete window;
    delete board;
}

void Gomoku::StartGame()
{
    this->initButtons();
    while (this->window->isOpen())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
            {
                if (!this->gomokuRule.GetIsGameEnded())
                {
                    if (this->checkIfInsideBoard(sf::Mouse::getPosition(*this->window)))
                    {
                        this->placeStone();
                        this->shouldEnableIndicator = !this->gomokuRule.GetIsGameEnded();
                    }
                }
                for (Button *buttonPtr : this->buttons)
                {
                    buttonPtr->OnClick();
                }
            }
            if (event.type == sf::Event::Closed)
            {
                this->window->close();
            }
        }
        this->window->clear(sf::Color::White);
        this->drawBoard();

        for (Button *buttonPtr : this->buttons)
        {
            this->drawButton(*buttonPtr);
        }

        if (this->shouldEnableIndicator && this->checkIfInsideBoard(sf::Mouse::getPosition(*this->window)))
        {
            this->drawIndicator(sf::Mouse::getPosition(*this->window));
        }
        this->drawStonesPlaced();
        
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

void Gomoku::initButtons()
{
    const sf::Vector2f &boardPosition = this->board->GetBoardPosition();
    sf::Vector2f buttonSize(this->board->GetBoardSize() / 4.f, this->board->GetBoardSize() / 12.f);

    sf::Vector2f buttonPosition(boardPosition.x + this->board->GetBoardSize() + buttonSize.y, boardPosition.y);
    sf::Vector2f buttonPosition2(buttonPosition.x, buttonPosition.y + buttonSize.y * 1.5f);
    sf::Vector2f buttonPosition3(buttonPosition.x, buttonPosition2.y + buttonSize.y * 1.5f);
    sf::Vector2f gomokuButtonPosition(buttonPosition.x, buttonPosition3.y + buttonSize.y * 1.5f);
    sf::Vector2f renjuButtonPosition(buttonPosition.x, gomokuButtonPosition.y + buttonSize.y * 1.5f);
    sf::Vector2f readFromTextFileButtonPosition(buttonPosition.x, renjuButtonPosition.y + buttonSize.y * 1.5f);
    sf::Vector2f exportButtonPosition(buttonPosition.x, readFromTextFileButtonPosition.y + buttonSize.y * 1.5f);

    Button *resetButton = new Button(this->window, "RESET STONES", this->font);
    resetButton->SetPosition(buttonPosition);
    resetButton->SetSize(buttonSize);
    this->buttons.push_back(resetButton);

    Button *labelToggleButton = new Button(this->window, "TOGGLE LABELS", this->font);
    labelToggleButton->SetPosition(buttonPosition2);
    labelToggleButton->SetSize(buttonSize);
    this->buttons.push_back(labelToggleButton);

    Button *undoButton = new Button(this->window, "UNDO", this->font);
    undoButton->SetPosition(buttonPosition3);
    undoButton->SetSize(buttonSize);
    this->buttons.push_back(undoButton);

    Button *gomokuButton = new Button(this->window, "GOMOKU", this->font);
    gomokuButton->SetPosition(gomokuButtonPosition);
    gomokuButton->SetSize(buttonSize);
    this->buttons.push_back(gomokuButton);

    Button *renjuButton = new Button(this->window, "RENJU", this->font);
    renjuButton->SetPosition(renjuButtonPosition);
    renjuButton->SetSize(buttonSize);
    this->buttons.push_back(renjuButton);

    Button *readFromTextFileButton = new Button(this->window, "IMPORT", this->font);
    readFromTextFileButton->SetSize(buttonSize);
    readFromTextFileButton->SetPosition(readFromTextFileButtonPosition);
    this->buttons.push_back(readFromTextFileButton);

    Button *exportButton = new Button(this->window, "EXPORT", this->font);
    exportButton->SetSize(buttonSize);
    exportButton->SetPosition(exportButtonPosition);
    this->buttons.push_back(exportButton);

    resetButton->SetOnClick([this]() {
        this->gomokuRule.Reset();
        this->resetStones();
        this->shouldEnableIndicator = true;
    });

    labelToggleButton->SetOnClick([this]() {
        this->shouldDisplayLabels = !this->shouldDisplayLabels;
    });

    undoButton->SetOnClick([this]() {
        this->undoLastStone();
    });

    gomokuButton->SetOnClick([this]() {
        if (this->gomokuRule.GetRuleType() != GOMOKU)
        {
            std::cout << "The game rule has been changed to GOMOKU" << std::endl;
            this->gomokuRule.SetRuleType(GOMOKU);
        }
    });

    renjuButton->SetOnClick([this]() {
        if (this->gomokuRule.GetRuleType() != RENJU)
        {
            std::cout << "The game rule has been changed to RENJU" << std::endl;
            this->gomokuRule.SetRuleType(RENJU);
        }
    });

    readFromTextFileButton->SetOnClick([this]() {
        std::cout << "read from text file button clicked!" << std::endl;
        int matrix[15][15];
        this->reader.GetIntegerMatrix(matrix);
        this->gomokuRule.Reset();
        this->resetStones();
        this->placeStonesFromIntegerMatrix(matrix);
    });

    exportButton->SetOnClick([this]() {
        std::cout << "export button clicked!" << std::endl;
        int matrix[15][15];
        this->exportCurrentKiboToIntegerMatrix(matrix);
        this->reader.WriteIntegerMatrixToTextFile(matrix);
    });
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

void Gomoku::drawIndicator(const sf::Vector2i &localPosition)
{
    float indicatorSize = this->indicator.getSize().x;
    if (abs(cachedMousePositionX - localPosition.x) < this->stoneSize &&
        abs(cachedMousePositionY - localPosition.y) < this->stoneSize)
    {
        this->window->draw(this->indicator);
        return;
    }
    else
    {
        cachedMousePositionX = localPosition.x;
        cachedMousePositionY = localPosition.y;
    }

    sf::Vector2i index = this->board->CalculateStoneIndexByPosition(localPosition);
    sf::Vector2f positionOfIndicator = this->board->CalculateStonePositionToPlace(index, indicatorSize);
    if (index.x > -1 && index.x < Board::NUM_LINES && index.y > -1 && index.y < Board::NUM_LINES)
    {
        this->indicator.setPosition(sf::Vector2f(positionOfIndicator.x + indicatorSize / 2, positionOfIndicator.y + indicatorSize / 2));
        this->window->draw(this->indicator);
    }
}

bool Gomoku::placeStone()
{
    const sf::Vector2i localPosition(cachedMousePositionX, cachedMousePositionY);
    sf::Vector2i stoneIndex = this->board->CalculateStoneIndexByPosition(localPosition);
    sf::Vector2f positionToPlace = this->board->CalculateStonePositionToPlace(stoneIndex, this->stoneSize);

    if (this->stones[stoneIndex.y][stoneIndex.x] == nullptr)
    {
        if (stoneIndex.y > -1 && stoneIndex.y < Board::NUM_LINES && stoneIndex.x > -1 && stoneIndex.x < Board::NUM_LINES)
        {
            this->stones[stoneIndex.y][stoneIndex.x] = new Stone(this->stoneSize, sf::Vector2f(positionToPlace.x, positionToPlace.y),
                                                                 ++counter, stoneIndex.x, stoneIndex.y);
            this->stones[stoneIndex.y][stoneIndex.x]->EnableLabel(font);
            this->stonesInOrder.push_back(this->stones[stoneIndex.y][stoneIndex.x]);
            if (this->gomokuRule.MakeMove(stoneIndex.x, stoneIndex.y, counter % 2))
            {
                this->indicator.setFillColor(this->counter % 2 == 0 ? sf::Color::Black : sf::Color::White);
            }
            else
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

void Gomoku::placeStonesFromIntegerMatrix(int (*matrix)[Board::NUM_LINES])
{
    for (int y = 0; y < Board::NUM_LINES; y++)
    {
        for (int x = 0; x < Board::NUM_LINES; x++)
        {
            if (matrix[y][x] != 0)
            {
                sf::Vector2f positionToPlace = this->board->CalculateStonePositionToPlace(sf::Vector2i(x, y), this->stoneSize);
                this->stones[y][x] = new Stone(this->stoneSize, sf::Vector2f(positionToPlace.x, positionToPlace.y),
                                               matrix[y][x], x, y);
                this->stones[y][x]->EnableLabel(font);
                this->stonesInOrder.push_back(this->stones[y][x]);
                counter++;
            }
        }
    }
}

void Gomoku::exportCurrentKiboToIntegerMatrix(int (*matrix)[Board::NUM_LINES]) const
{
    for (int y = 0; y < Board::NUM_LINES; y++)
    {
        for (int x = 0; x < Board::NUM_LINES; x++)
        {
            if (stones[y][x] != nullptr)
            {
                matrix[y][x] = stones[y][x]->GetCount();
            }
            else
            {
                matrix[y][x] = 0;
            }
        }
    }
}

bool Gomoku::checkIfInsideBoard(const sf::Vector2i &position) const
{
    return this->board->GetBoardArea().contains(sf::Vector2f(position.x, position.y));
}
