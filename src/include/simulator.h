#ifndef SIMULATOR_H
#define SIMULATOR_H

// Local include
#include "eventscheduler.h"
#include "stats.h"

// System include
#include <climits>

namespace lab1
{

class Simulator
{
public:
    Simulator();
    ~Simulator();

    void init(double simulationTime, double rho);
    const Stats& getStats(unsigned long queueLength, double simulationTime);

private:
    EventScheduler* ES;
};

template<class T>
void run(Simulator& sim, double simulationTime, T& output)
{   
    output << "simulationTime = " << simulationTime << "\n";
    output << "queue,rho,nObs,nArv,nDep,PIdle,PLoss,E_N,E_T\n";
    
#ifdef infQueue
    for(double rho = 0.25; rho <= 0.95; rho += 0.1)
    {
        sim.init(simulationTime, rho);
        output << "inf," << rho*100 << "," << sim.getStats(ULONG_MAX, simulationTime);
    }
#else
    unsigned K[3] = {5, 10, 40};
    
    for(double rho = 0.5; rho <= 1.5; rho += 0.1)
    {
        for(const unsigned k : K)
        {
            sim.init(simulationTime, rho);
            output << k << "," << rho*100 << "," << sim.getStats(k, simulationTime);
        }
    }
#endif
}
    
} // namespace lab1

#endif // SIMULATOR_H
