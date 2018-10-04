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

void Simulator::getStats(unsigned long queueLength, double simulationTime, 
                         double rho, std::ofstream output)
{
    Stats stats = ES->getStats(queueLength, simulationTime);
    output << queueLength << "," << rho << "," << stats;

#ifdef Debug
    std::cout << "**************************************\n"; 
    std::cout << "simulationTime = " << simulationTime << "\n";
    std::cout << "Queue size = " << queueLength << "\n";
    std::cout << "Utilization factor (rho) = " << rho << "\n";
    stats.print();
    std::cout << "**************************************\n";
#endif 
}

void Simulator::run(unsigned long queueLength, double simulationTime, std::ofstream output,
                    double rhoMin, double rhoMax, double step)
{   
    for(double rho = rhoMin; rho <= rhoMax; rho += step)
    {
        sim.init(simulationTime, rho);
        getStats(queueLength, simulationTime, rho, output);
    }
}
    
} // namespace lab1



