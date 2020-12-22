#pragma once

#include "board.h"
#include <map>

class Player;

class Game
{
public:
    explicit Game(const std::string_view &file);
    ~Game();

    void play(Player *player);
    unsigned short getRentValue();
    unsigned short getPurchaseValue();
    bool isGameOver();
    void addPlayer(const std::string &playerName);
    void resetGame();
    std::map<std::string, Player*> getPlayersMap();
    Player* getPlayer(const std::string_view & name);
    void setShouldIBuy(const std::string_view &name, const bool value);

private:
    std::unique_ptr<Board>board;
    int position;
    unsigned short isOut;
    std::map<std::string, Player*>playersMap;
    bool positionIsAvaiable();
    void setOwner(Player *player);
    Player* getOwnerOfProperty();
    void releaseAcquisitions(Player *player);
    void checkIsGameOver();
    unsigned short rollDice();
};
