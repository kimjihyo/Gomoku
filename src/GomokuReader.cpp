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
    int e;

    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            stream >> e;
            matrix[y][x] = e;
        }
    }
}

void GomokuReader::GetStoneMatrix(Stone *(*matrix)[Board::NUM_LINES])
{
}

void GomokuReader::WriteIntegerMatrixToTextFile(int (*matrix)[Board::NUM_LINES])
{
    std::ofstream stream(m_Filepath);
    for (int y = 0; y < Board::NUM_LINES; y++)
    {
        for (int x = 0; x < Board::NUM_LINES; x++)
        {
            stream << matrix[y][x] << " ";
        }
        stream << "\n";
    }
}