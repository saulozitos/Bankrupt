#pragma once

#include "board.h"
#include "player.h"
#include <memory>
class Game
{
public:
    explicit Game(const std::string &file);

    void play(Player *player);
    void rollDice(Player *player);
    unsigned short getRentValue();
    unsigned short getPurchaseValue();

    unsigned short getTotalPlayers() const;
    void setTotalPlayers(unsigned short value);

    bool isGameOver();

private:
    std::unique_ptr<Board>board;
    int position;
    unsigned short totalPlayers;
    unsigned short isOut;
    bool itsBuyable();
    void setOwner(Player *player);
    Player* getOwnerOfProperty();
    void releaseAcquisitions(Player *player);
    void checkIsGameOver();
};

