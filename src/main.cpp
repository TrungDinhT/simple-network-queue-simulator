// Local include
#include "simulator.h"

// System include
#include <iostream>
#include <fstream>

// Total simulation time (in s)
#define simulationTime 15000

// #define infQueue 1

using namespace lab1;

int main(void)
{
    Simulator sim;
    
#ifdef saveToCSV
    {
        std::ofstream dataFile;
#ifdef infQueue
        dataFile.open("output/data_infinite_queue.csv", std::ofstream::out | std::ofstream::trunc)
#else // #ifndef infQueue
        dataFile.open("output/data_finite_queue.csv", std::ofstream::out | std::ofstream::trunc);
#endif // #ifdef infQueue
        
        run<std::ofstream>(sim, simulationTime, dataFile);
        
        dataFile.close();
    }
#else // #ifndef saveToCSV
    {
        run<std::ostream>(sim, simulationTime, std::cout);
    }
#endif // #ifdef saveToCSV

    return 0;
}


