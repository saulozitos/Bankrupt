#pragma once
#include <string_view>
#include <memory>
#include "game.h"

class Simulation
{
public:
    explicit Simulation(const std::string_view & file);
    ~Simulation() = default;
    void runSimulation();
private:
    std::string fileConfiguration;
    std::unique_ptr<Game>game;
};

