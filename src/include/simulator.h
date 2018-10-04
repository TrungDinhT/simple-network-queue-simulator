#ifndef SIMULATOR_H
#define SIMULATOR_H

// Local include
#include "eventscheduler.h"
#include "stats.h"

// System include
#include <fstream>

namespace lab1
{

class Simulator
{
public:
    Simulator();
    ~Simulator();

    void init(double simulationTime, double rho);
    void getStats(unsigned long queueLength, double simulationTime, 
                  double rho, std::ofstream& output);
    void run(unsigned long queueLength, double simulationTime, unsigned numbersOfSteps, 
             double* rhoMin, double* rhoMax, double* step);

private:
    EventScheduler* ES;
};
    
} // namespace lab1

#endif // SIMULATOR_H
