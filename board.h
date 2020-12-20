#pragma once

#include "player.h"
#include <utility>

class Board {
protected:
  explicit Board(const std::string &file);
  std::vector<std::pair<std::pair<Player *, bool>, std::pair<int, int>>>
      boardData;

private:
  void loadConfigurationFile(const std::string_view f);
};
