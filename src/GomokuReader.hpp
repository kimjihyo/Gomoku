#pragma once
#include "Board.hpp"
#include "Stone.hpp"
#include <string>

class GomokuReader
{
private:
    std::string m_Filepath;
    std::string m_FileContentBuffer;
public:
    GomokuReader();
    ~GomokuReader();
    bool SetFilepath(const std::string &filepath);
    void GetIntegerMatrix(int (*matrix)[Board::NUM_LINES]);
    void GetStoneMatrix(Stone *(*matrix)[Board::NUM_LINES]);
    void WriteIntegerMatrixToTextFile(int (*matrix)[Board::NUM_LINES]);
};