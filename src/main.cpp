// Local include
#include "simulator.h"

// System include
#include <sstream>
#include <fstream>

// Total simulation time (in s)
#define simulationTime 15000

#define N 3

using namespace lab1;

int main(void)
{    
    Simulator sim;

    unsigned K[N] = {5, 10, 40};
    double rhoMin[N] = {0.4, 2, 5};
    double rhoMax[N] = {2, 5, 10};
    double step[N] = {0.1, 0.2, 0.4};
    std::ofstream dataFile[N];

    for(unsigned i = 0; i < N; i++)
    {
        std::sstream fileName("output/data_finite_queue_L_"); 
        fileName << K[i] << ".csv";

        dataFile[i].open(fileName.str(), std::ofstream::out | std::ofstream::trunc);
        dataFile[i] << "simulationTime = " << simulationTime << "\n";
        dataFile[i] << "queue,rho,nObs,nArv,nDep,PIdle,PLoss,E_N,E_T\n";

        for(unsigned j = 0; j < N; j++)
        {
            sim.run(K[i], simulationTime, dataFile, rhoMin[j], rhoMax[j], step[j]);
        }
    }
        
    dataFile.close();

    return 0;
}


