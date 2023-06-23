#include <raylib.h>

#include "simulation.h"

int main(void)
{
    Simulation simulation = initSimulation();
    startSimulation(&simulation);
    drawSimulation(&simulation);
    closeSimulation(&simulation);

    return 0;
}