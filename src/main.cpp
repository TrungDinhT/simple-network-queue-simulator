// Local include
#include "simulator.h"

// System include
#include <thread>
#include <string>

// Total simulation time (in s)
#define simulationTime 10000

using namespace lab1;

int main(void)
{
    /*
     * Init values for each kind of simulation
     */
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

    /*
     * Option for simulation acceleration by multithreading
     */
#ifdef multithreading
    std::vector<std::thread> threads;
    unsigned i = 0;
    Simulator sim[K.size()];
    
    for(const int k: K)
    {
        threads.push_back(std::thread(&Simulator::run, &sim[i], k, simulationTime, rhoMin, rhoMax, step));
        i++;
    }
    
    // Join all these threads
    for(unsigned i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
#else // #ifndef multithreading
    Simulator sim;
    
    for(const int k: K)
    {
        sim.run(k, simulationTime, rhoMin, rhoMax, step);
    }
#endif // #ifdef multithreading
    
    return 0;
}


