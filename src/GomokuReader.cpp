#include "GomokuReader.hpp"
#include "Board.hpp"
#include "Stone.hpp"
#include <string>
#include <fstream>
#include <iostream>

GomokuReader::GomokuReader()
{
}

GomokuReader::~GomokuReader()
{
}

bool GomokuReader::SetFilepath(const std::string &filepath)
{
    m_Filepath = filepath;
}

void GomokuReader::GetIntegerMatrix(int (*matrix)[Board::NUM_LINES])
{
    std::ifstream stream(m_Filepath);
    char ch;

    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            stream >> std::noskipws >> ch;
            if (ch == '\n')
            {
                stream >> std::noskipws >> ch;
            }
            if (ch != '\0')
            {
                matrix[y][x] = (int)ch - 48;
            }
        }
    }
}

void GomokuReader::GetStoneMatrix(Stone *(*matrix)[Board::NUM_LINES])
{
}