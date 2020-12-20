#include "game.h"

#include <iostream>
#include <random>

#define IS_DEBUG false

Game::Game(const std::string &file) : Board(file),
    position(0),
    totalPlayers(0),
    isOut(0)
{}

void Game::play(Player *player)
{
    if(isGameOver())
        return;

    if(player->getIsOut())
        return;

    const auto playerCoins = player->getCoins();

    #if IS_DEBUG
        std::cout << player->getId() << " - Coins: " << playerCoins << std::endl;
    #endif

    player->setPosition(position);

    if(itsBuyable() && player->getShouldIBuy())
    {
        const auto purchaseValue = getPurchaseValue();
        if(playerCoins > purchaseValue)
        {
            player->setCoins(playerCoins - purchaseValue);
            setOwner(player);
        }
        #if IS_DEBUG
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
            if(playerCoins > rentValue)
            {
                #if IS_DEBUG
                    std::cout<< player->getId() << " making payment of " << rentValue << " coins to " << owner->getId() << std::endl;
                #endif
                const auto newCoins = owner->getCoins() + rentValue;
                player->setCoins(playerCoins - rentValue);
                owner->setCoins(newCoins);
            }
            else
            {
                const auto newCoins = owner->getCoins() + rentValue;

                #if IS_DEBUG
                    std::cout<< player->getId() << " making payment of " << rentValue << " coins to " << owner->getId() << "  and exiting the game!" << std::endl;
                #endif

                player->setCoins(playerCoins - rentValue);
                player->setIsOut(true);

                #if IS_DEBUG
                    std::cout << player->getId() << " is now out of the game!" << std::endl;
                #endif

                isOut ++;
                owner->setCoins(newCoins);
                releaseAcquisitions(player);
            }
        }
        #if IS_DEBUG
        else
        {
            std::cout << "Nothing to do!" << std::endl;
        }
        #endif
    }
}

void Game::rollDice(Player *player)
{
    if(isGameOver())
        return;

    if(player->getIsOut())
        return;

    std::random_device r;

    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 6);
    const auto value = uniform_dist(e1);

#if IS_DEBUG
    std::cout << "\nDice value: " << value << std::endl;
#endif

    position = value + player->getPosition();
    if(position > 19)
    {
        const auto coins  = player->getCoins() + 100;
        player->setCoins(coins);
        position = position - 19;
    }

#if IS_DEBUG
    std::cout << player->getId() << " in position " << player->getPosition() << " go to position " << position << " - Position information:" << std::endl;

    if(itsBuyable())
    {
        std::cout << "Sale position! Purchase price: " << getPurchaseValue() << " coins - Rental price: " << getRentValue() << " coins!" << std::endl;
    }
    else
    {
        auto *owner = getOwnerOfProperty();
        std::cout << "This position belongs to " << owner->getId() << "! Rental price: " << getRentValue() << " coins!" << std::endl;
    }
#endif
}

unsigned short Game::getRentValue()
{
    return boardData[position].second.second;
}

unsigned short Game::getPurchaseValue()
{
    return boardData[position].second.first;
}

void Game::setTotalPlayers(unsigned short value)
{
    totalPlayers = value;
}

bool Game::isGameOver()
{
    return isOut == totalPlayers - 1;
}

bool Game::itsBuyable()
{
    return boardData[position].first.second;
}

void Game::setOwner(Player *player)
{
#if IS_DEBUG
    std::cout << player->getId() << " buying property " << position << "!" << std::endl;
#endif
    boardData[position].first.first = player;
    boardData[position].first.second = false;
    player->setProperties(position);
}

Player *Game::getOwnerOfProperty()
{
    return boardData[position].first.first;
}

void Game::releaseAcquisitions(Player *player)
{
    const auto proterties = player->getProperties();
    for(const auto &it : player->getProperties())
    {
        #if IS_DEBUG
            std::cout << "Releasing property " << it << " of " << player->getId() <<std::endl;
        #endif
        boardData[it].first.first = nullptr;
        boardData[it].first.second = true;
    }
}
