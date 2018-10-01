// Local include
#include "simulator.h"

namespace lab1
{
    
Simulator::Simulator()
  : ES(0)
{
}

Simulator::~Simulator()
{
    if(ES)
    {
        delete ES;
    }
}

void Simulator::init(double simulationTime, double rho)
{
    // Deallocate ES to prepare for new one
    if(ES)
    {
        delete ES;
        ES = 0;
    }
    ES = new EventScheduler();
    ES->init(simulationTime, rho);
}

const Stats& Simulator::getStats(unsigned long queueLength, double simulationTime)
{
    return ES->getStats(queueLength, simulationTime);
}
    
} // namespace lab1



