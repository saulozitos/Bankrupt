#include "player.h"

Player::Player(const std::string_view &playerId) :
    id(playerId),
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

void Player::addCoins(const int value)
{
    coins += value;
}

void Player::removeCoins(const int value)
{
    coins -= value;
}
