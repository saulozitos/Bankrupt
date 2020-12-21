#include "board.h"

#include <fstream>
#include <iostream>

Board::Board(const std::string_view &file)
{
    loadConfigurationFile(file);
}

void Board::loadConfigurationFile(const std::string_view &fileName)
{
    std::ifstream file(fileName.data());
    if(file.is_open())
    {
        unsigned short purchaseValue{0};
        unsigned short rentValue{0};

        while(file >> purchaseValue >> rentValue)
        {
            HouseProperty hp;
            hp.player = nullptr;
            hp.isAvaiable = true;
            hp.purchaseValue = purchaseValue;
            hp.rentValue = rentValue;
            data.push_back(hp);
        }
    }
    else
    {
        std::cout << "Filed to open " << fileName << std::endl;
    }
}
