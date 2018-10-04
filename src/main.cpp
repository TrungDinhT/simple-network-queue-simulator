// Local include
#include "simulator.h"

// System include
#include <thread>
#include <string>

// Total simulation time (in s)
#define simulationTime 15000

using namespace lab1;

int main(void)
{    
#ifndef infQueue
    std::vector<int> K = {5, 10, 40};
    std::vector<double> rhoMin = {0.4, 2, 5};
    std::vector<double> rhoMax = {2, 5, 10};
    std::vector<double> step = {0.1, 0.2, 0.4};
#else // #ifdef infQueue
    std::vector<int> K = {0}; // infinite Queue
    std::vector<double> rhoMin = {0.25};
    std::vector<double> rhoMax = {1.5};
    std::vector<double> step = {0.1};
#endif // #ifndef infQueue
    
    Simulator sim;

#ifdef multithreading
    std::vector<std::thread> threads;

    for(const int k: K)
    {
        threads.push_back(std::thread(&Simulator::run, &sim, k, simulationTime, rhoMin, rhoMax, step));
    }
    
    // Join all these threads
    for(unsigned i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
#else
    for(const int k: K)
    {
        sim.run(k, simulationTime, rhoMin, rhoMax, step);
    }
#endif
    
    return 0;
}


