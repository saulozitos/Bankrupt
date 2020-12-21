#pragma once

#include "player.h"
#include <string_view>
#include <memory>


struct HouseProperty
{
    Player *player;
    bool isAvaiable;
    unsigned short purchaseValue;
    unsigned short rentValue;
};

class Board
{
public:
    explicit Board(const std::string_view &file);
    std::vector<HouseProperty> data;

private:
    void loadConfigurationFile(const std::string_view &fileName);
};
