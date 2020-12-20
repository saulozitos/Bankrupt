#pragma once

#include <string>
#include <vector>

class Player {
public:
  explicit Player(std::string playerId);
  std::string getId() const;
  void setId(const std::string &value);

  int getCoins() const;
  void setCoins(int value);

  int getPosition() const;
  void setPosition(int value);

  std::vector<int> getProperties() const;
  void setProperties(int &value);

  bool getIsOut() const;
  void setIsOut(bool value);

  bool getShouldIBuy() const;
  void setShouldIBuy(bool value);

private:
  std::string id;
  int coins;
  int position;
  std::vector<int> properties;
  bool isOut;
  bool shouldIBuy;
};
