#include <iostream>
#include "GomokuRule.hpp"
#include "Stone.hpp"
#include "Board.hpp"

GomokuRule::GomokuRule() : m_Stones(nullptr)
{
}

GomokuRule::GomokuRule(Stone *stones[][Board::NUM_LINES]) : m_Stones(stones)
{
}

GomokuRule::~GomokuRule()
{
}

void GomokuRule::Reset()
{
    m_FiveStonesInRow.clear();
}

void GomokuRule::SetStones(Stone *stones[][Board::NUM_LINES])
{
    m_Stones = stones;
}

bool GomokuRule::CheckIfGameIsEnded(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType)
{
    return this->checkHorizontal(pivotX, pivotY, stoneType) ||
           this->checkVertical(pivotX, pivotY, stoneType) ||
           this->checkLeftDiagonal(pivotX, pivotY, stoneType) ||
           this->checkRightDiagonal(pivotX, pivotY, stoneType);
}

const std::vector<Stone *> &GomokuRule::GetFiveStonesInRow() const
{
    return m_FiveStonesInRow;
}

bool GomokuRule::checkHorizontal(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType)
{
    if (m_Stones[pivotY][pivotX] == nullptr)
    {
        return false;
    }

    int counter = -1;
    for (int i = pivotX; i > -1 && m_Stones[pivotY][i] != nullptr && m_Stones[pivotY][i]->GetCount() % 2 == stoneType; i--)
    {
        counter++;
    }
    for (int i = pivotX; i < Board::NUM_LINES && m_Stones[pivotY][i] != nullptr && m_Stones[pivotY][i]->GetCount() % 2 == stoneType; i++)
    {
        counter++;
    }

    std::cout << "horizontal count: " << counter << std::endl;

    return counter == 5;
}

bool GomokuRule::checkVertical(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType)
{
    if (m_Stones[pivotY][pivotX] == nullptr)
    {
        return false;
    }

    int counter = -1;
    for (int i = pivotY; i > -1 && m_Stones[i][pivotX] != nullptr && m_Stones[i][pivotX]->GetCount() % 2 == stoneType; i--)
    {
        counter++;
    }
    for (int i = pivotY; i < Board::NUM_LINES && m_Stones[i][pivotX] != nullptr && m_Stones[i][pivotX]->GetCount() % 2 == stoneType; i++)
    {
        counter++;
    }

    std::cout << "vertical count: " << counter << std::endl;

    return counter == 5;
}

bool GomokuRule::checkLeftDiagonal(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType)
{
    if (m_Stones[pivotY][pivotX] == nullptr)
    {
        return false;
    }
    int counter = -1;

    for (int x = pivotX, y = pivotY; x > -1 && y > -1 && m_Stones[y][x] != nullptr && m_Stones[y][x]->GetCount() % 2 == stoneType; x--, y--)
    {
        counter++;
    }
    for (int x = pivotX, y = pivotY; x < Board::NUM_LINES && y < Board::NUM_LINES && m_Stones[y][x] != nullptr && m_Stones[y][x]->GetCount() % 2 == stoneType; x++, y++)
    {
        counter++;
    }

    std::cout << "left diagonal count: " << counter << std::endl;
    return counter == 5;
}

bool GomokuRule::checkRightDiagonal(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType)
{
    if (m_Stones[pivotY][pivotX] == nullptr)
    {
        return false;
    }
    int counter = -1;
    for (int x = pivotX, y = pivotY; x < Board::NUM_LINES && y > -1 && m_Stones[y][x] != nullptr && m_Stones[y][x]->GetCount() % 2 == stoneType; x++, y--)
    {
        counter++;
    }
    for (int x = pivotX, y = pivotY; x > -1 && y < Board::NUM_LINES && m_Stones[y][x] != nullptr && m_Stones[y][x]->GetCount() % 2 == stoneType; x--, y++)
    {
        counter++;
    }

    std::cout << "right diagonal count: " << counter << std::endl;
    return counter == 5;
}