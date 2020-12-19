#include "game.h"
#include <iostream>
#include <random>

constexpr unsigned short IS_DEBUG = 0;

Game::Game(const std::string &file) :
    board(std::make_unique<Board>(file)),
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

    #ifdef IS_DEBUG
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
        #ifdef IS_DEBUG
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
                #ifdef IS_DEBUG
                    std::cout<< player->getId() << " making payment of " << rentValue << " coins to " << owner->getId() << std::endl;
                #endif
                const auto newCoins = owner->getCoins() + rentValue;
                player->setCoins(playerCoins - rentValue);
                owner->setCoins(newCoins);
            }
            else
            {
                const auto newCoins = owner->getCoins() + rentValue;

                #ifdef IS_DEBUG
                    std::cout<< player->getId() << " making payment of " << rentValue << " coins to " << owner->getId() << "  and exiting the game!" << std::endl;
                #endif

                player->setCoins(playerCoins - rentValue);
                player->setIsOut(true);

                #ifdef IS_DEBUG
                    std::cout << player->getId() << " is now out of the game!" << std::endl;
                #endif

                isOut ++;
                owner->setCoins(newCoins);
                releaseAcquisitions(player);
            }
        }
        #ifdef IS_DEBUG
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

#ifdef IS_DEBUG
    std::cout << "\nDice value: " << value << std::endl;
#endif

    position = value + player->getPosition();
    if(position > 19)
    {
        const auto coins  = player->getCoins() + 100;
        player->setCoins(coins);
        position = position - 19;
    }

#ifdef IS_DEBUG
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
    return board->data[position].second.second;
}

unsigned short Game::getPurchaseValue()
{
    return board->data[position].second.first;
}

unsigned short Game::getTotalPlayers() const
{
    return totalPlayers;
}

void Game::setTotalPlayers(unsigned short value)
{
    totalPlayers = value;
}

bool Game::isGameOver()
{
    return isOut == getTotalPlayers() - 1;
}

bool Game::itsBuyable()
{
    return board->data[position].first.second;
}

void Game::setOwner(Player *player)
{
#ifdef IS_DEBUG
    std::cout << player->getId() << " buying property " << position << "!" << std::endl;
#endif
    board->data[position].first.first = player;
    board->data[position].first.second = false;
    player->setProperties(position);
}

Player *Game::getOwnerOfProperty()
{
    return board->data[position].first.first;
}

void Game::releaseAcquisitions(Player *player)
{
    const auto proterties = player->getProperties();
    for(const auto &it : player->getProperties())
    {
        #ifdef IS_DEBUG
            std::cout << "Releasing property " << it << " of " << player->getId() <<std::endl;
        #endif
        board->data[it].first.first = nullptr;
        board->data[it].first.second = true;
    }
}
