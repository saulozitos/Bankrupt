#include "game.h"

#include <iostream>
#include <random>

Game::Game(const std::string_view &file) :
    board(std::make_unique<Board>(file)),
    position(0),
    isOut(0)
{}

void Game::play(Player *player)
{
    if(isGameOver())
        return;

    if(player->getIsOut())
        return;

    position = rollDice() + player->getPosition();
    if(position > 19)
    {
        player->addCoins(100);
        position = position - 19;
    }

    #if DEBUG
        std::cout << player->getId() << " in position " << player->getPosition() << " go to position " << position << " - Position information:" << std::endl;
        std::cout << player->getId() << " - Coins: " << player->getCoins() << std::endl;
    #endif

    player->setPosition(position);

    if(positionIsAvaiable() && player->getShouldIBuy())
    {
        #if DEBUG
        std::cout << "Sale position! Purchase price: " << getPurchaseValue() << " coins - Rental price: " << getRentValue() << " coins!" << std::endl;
        #endif

        const auto purchaseValue = getPurchaseValue();
        if(player->getCoins() > purchaseValue)
        {
            player->removeCoins(purchaseValue);
            setOwner(player);
        }
        #if DEBUG
        else
        {
            std::cout << "Insufficient coins to buy!" << std::endl;
        }
        #endif
    }
    else
    {
        auto *owner = getOwnerOfProperty();

        if(owner != nullptr && player != owner )
        {
            const auto rentValue = getRentValue();
            if(player->getCoins() > rentValue)
            {
                #if DEBUG
                    std::cout << "This position belongs to " << owner->getId() << "! Rental price: " << getRentValue() << " coins!" << std::endl;
                    std::cout<< player->getId() << " making payment of " << rentValue << " coins to " << owner->getId() << std::endl;
                #endif
                player->removeCoins(rentValue);
                owner->addCoins(rentValue);
                #if DEBUG
                    std::cout << player->getId() << " - Coins: " << player->getCoins() << std::endl;
                #endif
            }
            else
            {
                #if DEBUG
                    std::cout << "This position belongs to " << owner->getId() << "! Rental price: " << getRentValue() << " coins!" << std::endl;
                    std::cout << player->getId() << " making payment of " << rentValue << " coins to " << owner->getId() << "  and exiting the game!" << std::endl;
                #endif

                player->removeCoins(rentValue);
                player->setIsOut(true);

                #if DEBUG
                    std::cout << player->getId() << " is now out of the game!" << std::endl;
                #endif

                isOut ++;
                owner->addCoins(rentValue);
                releaseAcquisitions(player);
            }
        }
        #if DEBUG
        else
        {
            std::cout << "Nothing to do!" << std::endl;
        }
        #endif
    }
}

unsigned short Game::rollDice()
{
    std::random_device r;

    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 6);
    unsigned short value = uniform_dist(e1);
#if DEBUG
    std::cout << "\nDice value: " << value << std::endl;
#endif
    return value;
}

unsigned short Game::getRentValue()
{
    return board->data[position].rentValue;
}

unsigned short Game::getPurchaseValue()
{
    return board->data[position].purchaseValue;
}

bool Game::isGameOver()
{
    return isOut == playersMap.size() - 1;
}

void Game::addPlayer(const std::string &playerName)
{
    Player * player = new Player(playerName);
    playersMap.insert({playerName, player});
}

void Game::resetGame()
{
    for(const auto &it : playersMap)
        delete it.second;

    playersMap.erase(playersMap.begin(), playersMap.end());
}

std::map<std::string, Player *> Game::getPlayersMap()
{
    return playersMap;
}

Player *Game::getPlayer(const std::string_view &name)
{
    return playersMap[name.data()];
}

void Game::setShouldIBuy(const std::string_view &name, const bool value)
{
    playersMap[name.data()]->setShouldIBuy(value);
}

bool Game::positionIsAvaiable()
{
    return board->data[position].isAvaiable;
}

void Game::setOwner(Player *player)
{
#if DEBUG
    std::cout << player->getId() << " buying property " << position << "!" << std::endl;
#endif
    board->data[position].player = player;
    board->data[position].isAvaiable = false;
    player->setProperties(position);
}

Player *Game::getOwnerOfProperty()
{
    return board->data[position].player;
}

void Game::releaseAcquisitions(Player *player)
{
    const auto proterties = player->getProperties();
    for(const auto &it : player->getProperties())
    {
        #if DEBUG
            std::cout << "Releasing property " << it << " of " << player->getId() <<std::endl;
        #endif
        board->data[it].player = nullptr;
        board->data[it].isAvaiable = true;
    }
}
