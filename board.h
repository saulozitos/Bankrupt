#pragma once

#include <string>
#include <vector>
#include <utility>
#include <string_view>
#include <player.h>

class Board
{
public:
    explicit Board(const std::string &file);
    std::vector<std::pair< std::pair<Player*, bool>, std::pair<int, int> >>data;

private:
    void loadConfigurationFile(const std::string_view f);
};

