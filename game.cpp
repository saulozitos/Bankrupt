#include "game.h"

#include <iostream>
#include <random>
#include <memory>

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

    position = rollDice() + player->getPosition();
    if(position > 19)
    {
        const auto coins  = player->getCoins() + 100;
        player->setCoins(coins);
        position = position - 19;
    }

    const auto playerCoins = player->getCoins();

    #if DEBUG
        std::cout << player->getId() << " in position " << player->getPosition() << " go to position " << position << " - Position information:" << std::endl;
        std::cout << player->getId() << " - Coins: " << playerCoins << std::endl;
    #endif

    player->setPosition(position);

    if(itsBuyable() && player->getShouldIBuy())
    {
        #if DEBUG
        std::cout << "Sale position! Purchase price: " << getPurchaseValue() << " coins - Rental price: " << getRentValue() << " coins!" << std::endl;
        #endif

        const auto purchaseValue = getPurchaseValue();
        if(playerCoins > purchaseValue)
        {
            player->setCoins(playerCoins - purchaseValue);
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
            if(playerCoins > rentValue)
            {
                #if DEBUG
                    std::cout << "This position belongs to " << owner->getId() << "! Rental price: " << getRentValue() << " coins!" << std::endl;
                    std::cout<< player->getId() << " making payment of " << rentValue << " coins to " << owner->getId() << std::endl;
                #endif
                const auto newCoins = owner->getCoins() + rentValue;
                player->setCoins(playerCoins - rentValue);
                owner->setCoins(newCoins);
                #if DEBUG
                    std::cout << player->getId() << " - Coins: " << player->getCoins() << std::endl;
                #endif
            }
            else
            {
                const auto newCoins = owner->getCoins() + rentValue;

                #if DEBUG
                    std::cout << "This position belongs to " << owner->getId() << "! Rental price: " << getRentValue() << " coins!" << std::endl;
                    std::cout << player->getId() << " making payment of " << rentValue << " coins to " << owner->getId() << "  and exiting the game!" << std::endl;
                #endif

                player->setCoins(playerCoins - rentValue);
                player->setIsOut(true);

                #if DEBUG
                    std::cout << player->getId() << " is now out of the game!" << std::endl;
                #endif

                isOut ++;
                owner->setCoins(newCoins);
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

void Game::addPlayer(const std::string &playerName)
{
    playersMap.insert({playerName, std::unique_ptr<Player>(new Player(playerName)).get()});
}

void Game::resetGame()
{
    playersMap.erase(playersMap.begin(), playersMap.end());
}

bool Game::itsBuyable()
{
    return boardData[position].first.second;
}

void Game::setOwner(Player *player)
{
#if DEBUG
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
        #if DEBUG
            std::cout << "Releasing property " << it << " of " << player->getId() <<std::endl;
        #endif
        boardData[it].first.first = nullptr;
        boardData[it].first.second = true;
    }
}
