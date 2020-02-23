#pragma once
#include "Stone.hpp"
#include "Board.hpp"
#include <vector>

struct Move
{
    int counter;
    bool isOpen;
};

class GomokuRule
{
private:
    Stone *(*m_Stones)[Board::NUM_LINES];
    std::vector<Stone *> m_FiveStonesInRow;
    bool m_IsGameEnded;

public:
    GomokuRule();
    GomokuRule(Stone *stones[][Board::NUM_LINES]);
    ~GomokuRule();
    void Reset();
    void SetStones(Stone *stones[][Board::NUM_LINES]);
    bool MakeMove(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType);
    bool GetIsGameEnded() const;
    const std::vector<Stone *> &GetFiveStonesInRow() const;

private:
    Move checkHorizontal(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType);
    Move checkVertical(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType);
    Move checkLeftDiagonal(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType);
    Move checkRightDiagonal(unsigned int pivotX, unsigned int pivotY, unsigned int stoneType);
    bool checkDoubleThree(const Move &horizontal, const Move &vertical, const Move &leftDiagonal, const Move &rightDiagonal);
    bool checkDoubleFour(const Move &horizontal, const Move &vertical, const Move &leftDiagonal, const Move &rightDiagonal);
};