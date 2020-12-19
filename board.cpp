#include "board.h"
#include <fstream>
#include <iostream>

Board::Board(const std::string &file)
{
    loadConfigurationFile(file);
}

void Board::loadConfigurationFile(const std::string_view f)
{
    std::ifstream file(f.data());
    if(file.is_open())
    {
        int purchaseValue{0};
        int rentValue{0};

        while(file >> purchaseValue >> rentValue)
            data.push_back(std::make_pair(
                                    std::make_pair(nullptr, true),
                                    std::make_pair(purchaseValue, rentValue)));
    }
    else
    {
        std::cout << "Filed to open " << f << std::endl;
    }
}
