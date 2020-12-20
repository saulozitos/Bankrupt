#pragma once

#include "board.h"

class Player;

class Game : public Board {
public:
  explicit Game(const std::string &file);
  ~Game() = default;

  void play(Player *player);
  void rollDice(Player *player);
  unsigned short getRentValue();
  unsigned short getPurchaseValue();
  void setTotalPlayers(unsigned short value);
  bool isGameOver();

private:
  int position;
  unsigned short totalPlayers;
  unsigned short isOut;
  bool itsBuyable();
  void setOwner(Player *player);
  Player *getOwnerOfProperty();
  void releaseAcquisitions(Player *player);
  void checkIsGameOver();
};
