#include <iostream>
#include <algorithm>
#include <map>
#include <memory>
#include "game.h"
#include "player.h"

int main()
{
    const std::string fileConfiguration = "/home/saulo/Dev/Bankrupt/gameConfig.txt";
    auto game = std::make_unique<Game>(fileConfiguration);

    const std::string namePlayer1 = "Player1";
    const std::string namePlayer2 = "Player2";
    const std::string namePlayer3 = "Player3";
    const std::string namePlayer4 = "Player4";

    game->addPlayer(namePlayer1);
    game->addPlayer(namePlayer2);
    game->addPlayer(namePlayer3);
    game->addPlayer(namePlayer4);

    auto players = game->getPlayersMap();

    // player name, timeout wins, normal wins
    std::map<std::string, std::pair<int, int>> countWins;

    for(const auto &it : players)
        countWins.insert({it.first, {0, 0}});

    unsigned short totalMatch{300};
    unsigned short round{0};
    unsigned short timeOutRound{1000};
    unsigned short totalRounds{0};

    for (unsigned short match = 1; match <= totalMatch; ++match)
    {
        #if DEBUG
            std::cout << "\nRunning simulation #" << match << std::endl;
        #endif
        while (!game->isGameOver() && round < timeOutRound)
        {
            for (const auto &it : players)
            {
                game->play(it.second);
                const auto rentValue = game->getRentValue();
                const auto purchaseValue = game->getPurchaseValue();

                game->setShouldIBuy(namePlayer1, true);
                game->setShouldIBuy(namePlayer2, rentValue > 50);
                game->setShouldIBuy(namePlayer3, game->getPlayer(namePlayer3)->getCoins() - purchaseValue >= 80);
                game->setShouldIBuy(namePlayer4, round % 2 == 0);
            }
            round++;
        }

        totalRounds += round;

        const bool isGameTimeout = round == timeOutRound;
        if (isGameTimeout || game->isGameOver())
        {
            std::vector<std::pair<int, std::string>> players{
                {game->getPlayer(namePlayer1)->getCoins(), game->getPlayer(namePlayer1)->getId()},
                {game->getPlayer(namePlayer2)->getCoins(), game->getPlayer(namePlayer2)->getId()},
                {game->getPlayer(namePlayer3)->getCoins(), game->getPlayer(namePlayer3)->getId()},
                {game->getPlayer(namePlayer4)->getCoins(), game->getPlayer(namePlayer4)->getId()},
            };

            const auto winner = *std::max_element(players.begin(), players.end());
            const auto playerName = winner.second;

            if (isGameTimeout)
            {
                std::cout << "In simulation #" << match
                          << " the game ended by time out - The winner is "
                          << playerName << std::endl;
                countWins[playerName].first += 1;
            }
            else
            {
                std::cout << "In simulation #" << match << " the game ended in round "
                          << round << " - The winner is " << playerName << std::endl;
                countWins[playerName].second += 1;
            }
        }

        game->resetGame();
        game.release();

        players.erase(players.begin(), players.end());

        round = 0;

        game = std::make_unique<Game>(fileConfiguration);

        game->addPlayer(namePlayer1);
        game->addPlayer(namePlayer2);
        game->addPlayer(namePlayer3);
        game->addPlayer(namePlayer4);

        players = game->getPlayersMap();
        for(const auto &it : players)
            countWins.insert({it.first, {0, 0}});

    }

    int totalTimeOutWins{0};
    int totalNormalWins{0};

    std::cout << "\nGame analysis:" << std::endl;
    for (const auto &it : countWins)
    {
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
