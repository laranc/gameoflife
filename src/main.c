#include <stdlib.h>
#include <time.h>

#include "simulation.h"

i32 main(void) {
  srand(time(NULL));

  Simulation *simulation = simulationInit();
  simulationStart(simulation);
  simulationUpdate(simulation);
  simulationClose(simulation);

  return 0;
}
