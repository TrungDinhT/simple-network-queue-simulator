// Local include
#include "simulator.h"

// System include
#include <sstream>
#include <fstream>
#include <climits>

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
                         double rho, std::ofstream& output)
{
    Stats stats = ES->getStats(queueLength, simulationTime);
    (queueLength == ULONG_MAX) ? output << "inf" << "," << rho << ","
                               : output << queueLength << "," << rho << ",";
    output << stats;

#ifdef Debug
    std::cout << "**************************************\n"; 
    std::cout << "simulationTime = " << simulationTime << "\n";
    (queueLength == ULONG_MAX) ? std::cout << "Queue size = inf" << "\n"
                               : std::cout << "Queue size = " << queueLength << "\n";
    std::cout << "Utilization factor (rho) = " << rho << "\n";
    stats.print();
    std::cout << "**************************************\n";
#endif 
}

void Simulator::run(unsigned long queueLength, double simulationTime, unsigned numbersOfSteps, 
                    double* rhoMin, double* rhoMax, double* step)
{
    std::ofstream dataFile;
    std::stringstream fileName("output/data_queue_size_"); 
    (queueLength == ULONG_MAX) ? fileName << queueLength << ".csv"
                               : fileName << "inf.csv";

    dataFile.open(fileName.str(), std::ofstream::out | std::ofstream::trunc);

    dataFile << "simulationTime = " << simulationTime << "\n";
    dataFile << "queue,rho,nObs,nArv,nDep,PIdle,PLoss,E_N,E_T\n";
    for(unsigned i = 0; i < numbersOfSteps; i++)
    {
        for(double rho = rhoMin[i]; rho <= rhoMax[i]; rho += step[i])
        {
            init(simulationTime, rho);
            getStats(queueLength, simulationTime, rho, dataFile);
        }    
    }

    dataFile.close();
}
    
} // namespace lab1



