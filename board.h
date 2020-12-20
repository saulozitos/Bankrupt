#pragma once

#include <utility>
#include <player.h>

class Board
{
protected:
    explicit Board(const std::string &file);
    std::vector<std::pair< std::pair<Player*, bool>, std::pair<int, int> >>boardData;

private:
    void loadConfigurationFile(const std::string_view f);
};

