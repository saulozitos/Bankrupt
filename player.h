#pragma once

#include <string>
#include <string_view>
#include <vector>

class Player
{
public:
    explicit Player(const std::string_view &playerId);
    ~Player() = default;

    std::string getId() const;
    void setId(const std::string &value);

    int getCoins() const;

    int getPosition() const;
    void setPosition(int value);

    std::vector<int> getProperties() const;
    void addProperties(int &value);

    bool getIsOut() const;
    void setIsOut(bool value);

    bool getShouldIBuy() const;
    void setShouldIBuy(bool value);

    void addCoins(const int value);
    void removeCoins(const int value);

private:
    std::string id;
    int coins;
    int position;
    std::vector<int> properties;
    bool isOut;
    bool shouldIBuy;
};
