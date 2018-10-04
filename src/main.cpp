// Local include
#include "simulator.h"

// System include
#include <climits>

// Total simulation time (in s)
#define simulationTime 15000

using namespace lab1;

int main(void)
{    
    Simulator sim;

#ifndef infQueue
    unsigned numbersOfSteps = 3;
    unsigned K[3] = {5, 10, 40};
    double rhoMin[numbersOfSteps] = {0.4, 2, 5};
    double rhoMax[numbersOfSteps] = {2, 5, 10};
    double step[numbersOfSteps] = {0.1, 0.2, 0.4};
#else // #ifdef infQueue
    unsigned numbersOfSteps = 1;
    unsigned K[1] = {ULONG_MAX};
    double rhoMin[numbersOfSteps] = {0.25};
    double rhoMax[numbersOfSteps] = {1.5};
    double step[numbersOfSteps] = {0.1};
#endif // #ifndef infQueue

    for(const unsigned k: K)
    {
        sim.run(k, simulationTime, numbersOfSteps, rhoMin, rhoMax, step);
    }

    return 0;
}


