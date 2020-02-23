#include "GomokuReader.hpp"
#include "Board.hpp"
#include "Stone.hpp"
#include <string>
#include <fstream>

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
    
    while (stream >> std::noskipws >> ch)
    {
        // Process chracters
    }
}

void GomokuReader::GetStoneMatrix(Stone* (*matrix)[Board::NUM_LINES])
{

}