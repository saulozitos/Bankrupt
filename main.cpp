#include <string>
#include "simulation.h"

int main()
{
    const std::string fileConfiguration = "/home/saulo/Dev/Bankrupt/gameConfig.txt";

    Simulation simulation(fileConfiguration);
    simulation.runSimulation();
    return 0;
}
