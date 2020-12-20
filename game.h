#pragma once

#include "board.h"

#include <map>

class Player;

class Game : public Board
{
public:
    explicit Game(const std::string &file);
    ~Game() = default;

    void play(Player *player);
    unsigned short rollDice();
    unsigned short getRentValue();
    unsigned short getPurchaseValue();
    void setTotalPlayers(unsigned short value);
    bool isGameOver();
    void addPlayer(const std::string &playerName);
    void resetGame();

private:
    int position;
    unsigned short totalPlayers;
    unsigned short isOut;
    std::map<std::string, Player*>playersMap;
    bool itsBuyable();
    void setOwner(Player *player);
    Player* getOwnerOfProperty();
    void releaseAcquisitions(Player *player);
    void checkIsGameOver();
};
