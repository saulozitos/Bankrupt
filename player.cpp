#include "player.h"

Player::Player(std::string playerId) :
    id(std::move(playerId)),
    coins(300),
    position(-1),
    isOut(false),
    shouldIBuy(false)
{}

std::string Player::getId() const
{
    return id;
}

void Player::setId(const std::string &value)
{
    id = value;
}

int Player::getCoins() const
{
    return coins;
}

void Player::setCoins(int value)
{
    coins = value;
}

int Player::getPosition() const
{
    return position;
}

void Player::setPosition(int value)
{
    position = value;
}

std::vector<int> Player::getProperties() const
{
    return properties;
}

void Player::setProperties(int &value)
{
    properties.push_back(value);
}

bool Player::getIsOut() const
{
    return isOut;
}

void Player::setIsOut(bool value)
{
    isOut = value;
}

bool Player::getShouldIBuy() const
{
    return shouldIBuy;
}

void Player::setShouldIBuy(bool value)
{
    shouldIBuy = value;
}
