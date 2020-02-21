#pragma once
#include "Stone.hpp"
#include "Board.hpp"
#include <vector>

class GomokuRule
{
private:
    Stone *(*m_Stones)[Board::NUM_LINES];
    std::vector<Stone*> m_FiveStonesInRow;

public:
    GomokuRule();
    GomokuRule(Stone *stones[][Board::NUM_LINES]);
    ~GomokuRule();
    void Reset();
    void SetStones(Stone *stones[][Board::NUM_LINES]);
    bool CheckIfGameIsEnded(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType);
    const std::vector<Stone*>& GetFiveStonesInRow() const;

private:
    bool checkHorizontal(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType);
    bool checkVertical(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType);
    bool checkDiagonal(const unsigned int pivotX, const unsigned int pivotY, const unsigned int stoneType);
};