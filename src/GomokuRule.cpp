#include <iostream>
#include "GomokuRule.hpp"
#include "Stone.hpp"
#include "Board.hpp"

GomokuRule::GomokuRule() : m_Stones(nullptr), m_IsGameEnded(false)
{
}

GomokuRule::GomokuRule(Stone *stones[][Board::NUM_LINES]) : m_IsGameEnded(false)
{
    m_Stones = stones;
}

GomokuRule::~GomokuRule()
{
}

void GomokuRule::Reset()
{
    m_IsGameEnded = false;
    m_FiveStonesInRow.clear();
}

void GomokuRule::SetStones(Stone *stones[][Board::NUM_LINES])
{
    m_Stones = stones;
}

bool GomokuRule::IsGameEnded() const
{
    return m_IsGameEnded;
}

bool GomokuRule::CheckIfGameIsEnded(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType)
{
    m_IsGameEnded = this->checkHorizontal(pivotX, pivotY, stoneType) || this->checkVertical(pivotX, pivotY, stoneType);
    return m_IsGameEnded;
}

const std::vector<Stone *> &GomokuRule::GetFiveStonesInRow() const
{
    return m_FiveStonesInRow;
}

bool GomokuRule::checkHorizontal(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType)
{
    Stone *pivotStone = m_Stones[pivotY][pivotX];
    if (pivotStone == nullptr)
    {
        return false;
    }
    int counter = 0;
    Stone *currentStone = nullptr;
    bool isGomoku = false;
    for (int i = 0; i < Board::NUM_LINES; i++)
    {
        currentStone = m_Stones[pivotY][i];
        if (currentStone != nullptr && currentStone->GetCount() % 2 == stoneType)
        {
            ++counter;
            m_FiveStonesInRow.push_back(currentStone);
            if (counter == 5)
            {
                isGomoku = true;
            }
            else if (counter > 5)
            {
                m_FiveStonesInRow.clear();
                return false;
            }
        }
        else
        {
            if (!isGomoku)
            {
                m_FiveStonesInRow.clear();
            }
            counter = 0;
        }
    }
    if (isGomoku)
    {
        std::cout << "Gomoku!" << std::endl;
    }
    return isGomoku;
}

bool GomokuRule::checkVertical(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType)
{
    Stone *pivotStone = m_Stones[pivotY][pivotX];
    if (pivotStone == nullptr)
    {
        return false;
    }
    int counter = 0;
    bool isGomoku = false;
    Stone *currentStone = nullptr;
    for (int i = 0; i < Board::NUM_LINES; i++)
    {
        currentStone = m_Stones[i][pivotX];
        if (currentStone != nullptr && currentStone->GetCount() % 2 == stoneType)
        {
            ++counter;
            m_FiveStonesInRow.push_back(currentStone);
            if (counter == 5)
            {
                isGomoku = true;
            }
            else if (counter > 5)
            {
                m_FiveStonesInRow.clear();
                return false;
            }
        }
        else
        {
            if (!isGomoku)
            {
                m_FiveStonesInRow.clear();
            }
            counter = 0;
        }
    }
    if (isGomoku)
    {
        std::cout << "Gomoku!" << std::endl;
    }
    return isGomoku;
}

bool GomokuRule::checkDiagonal(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType)
{
    
}