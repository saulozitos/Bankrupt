#include <iostream>

#include "player.h"
#include <algorithm>
#include <map>
#include <memory>

#include "game.h"
#include "player.h"

int main() {
  const std::string fileConfiguration =
      "/home/andreagenor/code/tmp/Bankrupt/gameConfig.txt";
  auto game = std::make_unique<Game>(fileConfiguration);

  // ​Compra qualquer propriedade sobre a qual ele parar.
  auto player1 = std::make_unique<Player>("Player1");

  // ​Compra qualquer propriedade, desde que o aluguel dela seja maior do​
  // ​que 50 ​coins.
  auto player2 = std::make_unique<Player>("Player2");

  // ​Compra qualquer propriedade, desde que ao final da compra ele possua uma
  // reserva maior ou igual a​ ​80 ​coins​.
  auto player3 = std::make_unique<Player>("Player3");

  // Compra a propriedade de maneira aleatória, com probabilidade de​ ​50%.
  auto player4 = std::make_unique<Player>("Player4");

  std::vector<Player *> players{player1.get(), player2.get(), player3.get(),
                                player4.get()};

  game->setTotalPlayers(players.size());

  unsigned short totalMatch{300};
  unsigned short round{0};
  unsigned short timeOutRound{1000};
  unsigned short totalRounds{0};

  // player name, timeout wins, normal wins
  std::map<std::string, std::pair<int, int>> countWins{
      {player1->getId(), {0, 0}},
      {player2->getId(), {0, 0}},
      {player3->getId(), {0, 0}},
      {player4->getId(), {0, 0}},
  };

  for (unsigned short match = 1; match <= totalMatch; ++match) {
    while (!game->isGameOver() && round < timeOutRound) {
      for (const auto &it : players) {
        game->rollDice(it);
        const auto rentValue = game->getRentValue();
        const auto purchaseValue = game->getPurchaseValue();
        player1->setShouldIBuy(true);
        player2->setShouldIBuy(rentValue > 50);
        player3->setShouldIBuy(player3->getCoins() - purchaseValue >= 80);
        player4->setShouldIBuy(round % 2 == 0);
        game->play(it);
      }
      round++;
    }

    totalRounds += round;

    const bool isGameTimeout = round == timeOutRound;
    if (isGameTimeout || game->isGameOver()) {
      std::vector<std::pair<int, std::string>> players{
          {player1->getCoins(), player1->getId()},
          {player2->getCoins(), player2->getId()},
          {player3->getCoins(), player3->getId()},
          {player4->getCoins(), player4->getId()},
      };

      const auto winner = *std::max_element(players.begin(), players.end());
      const auto playerName = winner.second;

      if (isGameTimeout) {
        std::cout << "In simulation #" << match
                  << " the game ended by time out - The winner is "
                  << playerName << std::endl;
        countWins[playerName].first += 1;
      } else {
        std::cout << "In simulation #" << match << " the game ended in round "
                  << round << " - The winner is " << playerName << std::endl;
        countWins[playerName].second += 1;
      }
    }

    game.release();
    player1.release();
    player2.release();
    player3.release();
    player4.release();
    players.erase(players.begin(), players.end());

    round = 0;

    game = std::make_unique<Game>(fileConfiguration);

    player1 = std::make_unique<Player>("Player1");
    player2 = std::make_unique<Player>("Player2");
    player3 = std::make_unique<Player>("Player3");
    player4 = std::make_unique<Player>("Player4");
    players = {player1.get(), player2.get(), player3.get(), player4.get()};

    game->setTotalPlayers(players.size());
  }

  int totalTimeOutWins{0};
  int totalNormalWins{0};

  std::cout << "\nGame analysis:" << std::endl;
  for (const auto &it : countWins) {
    const auto playerName = it.first;
    const auto timeOutWins = it.second.first;
    totalTimeOutWins += timeOutWins;
    const auto normalWins = it.second.second;
    totalNormalWins += normalWins;
    const auto totalWins = timeOutWins + normalWins;
    const float percentWiner = (totalWins * 100.00) / totalMatch;

    std::cout << playerName << " - time out wins: " << timeOutWins
              << " - normal wins: " << normalWins
              << " - Total wins: " << totalWins
              << " - Winning percentage: " << percentWiner << "%" << std::endl;
  }

  std::cout << "Total time out wins: " << totalTimeOutWins << std::endl;
  std::cout << "Total normal wins: " << totalNormalWins << std::endl;
  std::cout << "Average: " << totalRounds / totalMatch << std::endl;

  return 0;
}
