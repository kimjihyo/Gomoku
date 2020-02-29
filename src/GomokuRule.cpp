#include <iostream>
#include "GomokuRule.hpp"
#include "Stone.hpp"
#include "Board.hpp"

GomokuRule::GomokuRule() : m_Stones(nullptr), m_IsGameEnded(false), m_RuleType(RENJU)
{
}

GomokuRule::GomokuRule(Stone *stones[][Board::NUM_LINES]) : m_Stones(stones), m_IsGameEnded(false), m_RuleType(RENJU)
{
}

GomokuRule::~GomokuRule()
{
}

void GomokuRule::Reset()
{
    m_FiveStonesInRow.clear();
    m_IsGameEnded = false;
}

void GomokuRule::SetStones(Stone *stones[][Board::NUM_LINES])
{
    m_Stones = stones;
}

void GomokuRule::SetRuleType(RuleType ruleType)
{
    m_RuleType = ruleType;
}

bool GomokuRule::MakeMove(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType)
{
    Move horizontalMove = this->checkHorizontal(pivotX, pivotY, stoneType);
    Move verticalMove = this->checkVertical(pivotX, pivotY, stoneType);
    Move leftDiagonalMove = this->checkLeftDiagonal(pivotX, pivotY, stoneType);
    Move rightDiagonalMove = this->checkRightDiagonal(pivotX, pivotY, stoneType);

    m_IsGameEnded = (horizontalMove.counter == 5 && horizontalMove.isConnected) ||
                    (verticalMove.counter == 5 && verticalMove.isConnected) ||
                    (leftDiagonalMove.counter == 5 && leftDiagonalMove.isConnected) ||
                    (rightDiagonalMove.counter == 5 && rightDiagonalMove.isConnected);

    if (m_RuleType == RENJU)
    {
        if (stoneType == 0)
        {
            return true;
        }
        else
        {
            return !checkDoubleThree(horizontalMove, verticalMove, leftDiagonalMove, rightDiagonalMove) &&
                   !checkDoubleFour(horizontalMove, verticalMove, leftDiagonalMove, rightDiagonalMove) &&
                   !checkSixInARow(horizontalMove, verticalMove, leftDiagonalMove, rightDiagonalMove);
        }
    }
    else
    {
        return true;
    }
}

bool GomokuRule::GetIsGameEnded() const
{
    return m_IsGameEnded;
}

const std::vector<Stone *> &GomokuRule::GetFiveStonesInRow() const
{
    return m_FiveStonesInRow;
}

bool GomokuRule::GetRuleType() const
{
    return m_RuleType;
}

Move GomokuRule::checkHorizontal(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType) const
{
    int counter = 1;
    bool isOpen = true;
    bool canMoveForward = true;
    bool isConnected = true;
    for (int i = pivotX - 1; i > -1; i--)
    {
        if (m_Stones[pivotY][i] == nullptr)
        {
            if (canMoveForward)
            {
                canMoveForward = false;
                continue;
            }
            else
            {
                break;
            }
        }
        else if (m_Stones[pivotY][i]->GetCount() % 2 != stoneType)
        {
            isOpen = isConnected && !canMoveForward;
            break;
        }
        if (!canMoveForward)
        {
            isConnected = false;
        }
        counter++;
    }
    canMoveForward = isConnected;
    for (int i = pivotX + 1; i < Board::NUM_LINES; i++)
    {
        if (m_Stones[pivotY][i] == nullptr)
        {
            if (canMoveForward)
            {
                canMoveForward = false;
                continue;
            }
            else
            {
                break;
            }
        }
        if (m_Stones[pivotY][i]->GetCount() % 2 != stoneType)
        {
            isOpen = isConnected && !canMoveForward;
            break;
        }
        if (!canMoveForward)
        {
            isConnected = false;
        }
        counter++;
    }

    std::cout << "checkHorizontal:: " << counter << std::endl;
    std::cout << "checkHorizontal::isOpen:: " << isOpen << std::endl;
    std::cout << "checkHorizontal::isConnected:: " << isConnected << std::endl;
    return {counter, isOpen, isConnected};
}

Move GomokuRule::checkVertical(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType) const
{
    int counter = 1;
    bool isOpen = true;
    bool canMoveForward = true;
    bool isConnected = true;
    for (int i = pivotY - 1; i > -1; i--)
    {
        if (m_Stones[i][pivotX] == nullptr)
        {
            if (canMoveForward)
            {
                canMoveForward = false;
                continue;
            }
            else
            {
                break;
            }
        }
        if (m_Stones[i][pivotX]->GetCount() % 2 != stoneType)
        {
            isOpen = isConnected && !canMoveForward;
            break;
        }
        if (!canMoveForward)
        {
            isConnected = false;
        }
        counter++;
    }
    canMoveForward = isConnected;
    for (int i = pivotY + 1; i < Board::NUM_LINES; i++)
    {
        if (m_Stones[i][pivotX] == nullptr)
        {
            if (canMoveForward)
            {
                canMoveForward = false;
                continue;
            }
            else
            {
                break;
            }
        }
        if (m_Stones[i][pivotX]->GetCount() % 2 != stoneType)
        {
            isOpen = isConnected && !canMoveForward;
            break;
        }
        if (!canMoveForward)
        {
            isConnected = false;
        }
        counter++;
    }
    std::cout << "checkVertical:: " << counter << std::endl;
    std::cout << "checkVertical::isOpen:: " << isOpen << std::endl;
    std::cout << "checkHorizontal::isConnected:: " << isConnected << std::endl;

    return {counter, isOpen, isConnected};
}

Move GomokuRule::checkLeftDiagonal(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType) const
{
    int counter = 1;
    bool isOpen = true;
    bool canMoveForward = true;
    bool isConnected = true;
    for (int x = pivotX - 1, y = pivotY - 1; x > -1 && y > -1; x--, y--)
    {
        if (m_Stones[y][x] == nullptr)
        {
            if (canMoveForward)
            {
                canMoveForward = false;
                continue;
            }
            else
            {
                break;
            }
        }
        if (m_Stones[y][x]->GetCount() % 2 != stoneType)
        {
            isOpen = isConnected && !canMoveForward;
            break;
        }
        if (!canMoveForward)
        {
            isConnected = false;
        }
        counter++;
    }
    canMoveForward = isConnected;
    for (int x = pivotX + 1, y = pivotY + 1; x < Board::NUM_LINES && y < Board::NUM_LINES; x++, y++)
    {
        if (m_Stones[y][x] == nullptr)
        {
            if (canMoveForward)
            {
                canMoveForward = false;
                continue;
            }
            else
            {
                break;
            }
        }
        if (m_Stones[y][x]->GetCount() % 2 != stoneType)
        {
            isOpen = isConnected && !canMoveForward;
            break;
        }
        if (!canMoveForward)
        {
            isConnected = false;
        }
        counter++;
    }
    std::cout << "checkLeftDiagonal:: " << counter << std::endl;
    std::cout << "checkLeftDiagonal::isOpen:: " << isOpen << std::endl;
    std::cout << "checkHorizontal::isConnected:: " << isConnected << std::endl;

    return {counter, isOpen, isConnected};
}

Move GomokuRule::checkRightDiagonal(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType) const
{
    int counter = 1;
    bool isOpen = true;
    bool canMoveForward = true;
    bool isConnected = true;
    for (int x = pivotX + 1, y = pivotY - 1; x < Board::NUM_LINES && y > -1; x++, y--)
    {
        if (m_Stones[y][x] == nullptr)
        {
            if (canMoveForward)
            {
                canMoveForward = false;
                continue;
            }
            else
            {
                break;
            }
        }
        if (m_Stones[y][x]->GetCount() % 2 != stoneType)
        {
            isOpen = isConnected && !canMoveForward;
            break;
        }
        if (!canMoveForward)
        {
            isConnected = false;
        }
        counter++;
    }
    canMoveForward = isConnected;
    for (int x = pivotX - 1, y = pivotY + 1; x > -1 && y < Board::NUM_LINES; x--, y++)
    {
        if (m_Stones[y][x] == nullptr)
        {
            if (canMoveForward)
            {
                canMoveForward = false;
                continue;
            }
            else
            {
                break;
            }
        }
        if (m_Stones[y][x]->GetCount() % 2 != stoneType)
        {
            isOpen = isConnected && !canMoveForward;
            break;
        }
        if (!canMoveForward)
        {
            isConnected = false;
        }
        counter++;
    }
    std::cout << "checkRightDiagonal:: " << counter << std::endl;
    std::cout << "checkRightDiagonal::isOpen:: " << isOpen << std::endl;
    std::cout << "checkHorizontal::isConnected:: " << isConnected << std::endl;

    return {counter, isOpen, isConnected};
}

bool GomokuRule::checkDoubleThree(const Move &horizontal, const Move &vertical, const Move &leftDiagonal, const Move &rightDiagonal) const
{
    int counter = 0;
    if (horizontal.counter == 3 && horizontal.isOpen)
    {
        counter++;
    }
    if (vertical.counter == 3 && vertical.isOpen)
    {
        counter++;
    }
    if (leftDiagonal.counter == 3 && leftDiagonal.isOpen)
    {
        counter++;
    }
    if (rightDiagonal.counter == 3 && rightDiagonal.isOpen)
    {
        counter++;
    }
    std::cout << std::endl
              << "checkDoubleThree::counter:: " << counter << std::endl;
    return counter > 1;
}
bool GomokuRule::checkDoubleFour(const Move &horizontal, const Move &vertical, const Move &leftDiagonal, const Move &rightDiagonal) const
{
    int counter = 0;
    if (horizontal.counter == 4 && horizontal.isOpen)
    {
        counter++;
    }
    if (vertical.counter == 4 && vertical.isOpen)
    {
        counter++;
    }
    if (leftDiagonal.counter == 4 && leftDiagonal.isOpen)
    {
        counter++;
    }
    if (rightDiagonal.counter == 4 && rightDiagonal.isOpen)
    {
        counter++;
    }
    return counter > 1;
}

bool GomokuRule::checkSixInARow(const Move &horizontal, const Move &vertical, const Move &leftDiagonal, const Move &rightDiagonal) const
{
    return (horizontal.counter == 6 && horizontal.isConnected) ||
           (vertical.counter == 6 && vertical.isConnected) ||
           (leftDiagonal.counter == 6 && leftDiagonal.isConnected) ||
           (rightDiagonal.counter == 6 && rightDiagonal.isConnected);
}

bool GomokuRule::checkIfStonePlacedAt(unsigned int x, unsigned int y)
{
    return x < Board::NUM_LINES && y < Board::NUM_LINES && m_Stones[y][x] == nullptr;
}