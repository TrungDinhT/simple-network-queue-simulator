// Local include
#include "stats.h"

// System include
#include <iostream>

namespace lab1
{

Stats::Stats(unsigned int T)
  : nObs(0),
    nArv(0),
    nDep(0),
    nIdle(0),
    E_T(0.0),
    E_N(0.0),
    simulationTime(T)
{
}

Stats::~Stats()
{
}

void Stats::process(std::vector<Event*>& eventQueue)
{
    while(!eventQueue.empty())
    {
        Event* event = eventQueue.back();
        
        if(event->evtType() == Obs)
        {
            nObs++;
            if(nArv > nDep)
            {
                E_N += nArv - nDep;
            }
            else if(nArv == nDep)
            {
                nIdle++;
            }
            else
            {
                std::cerr << "ERROR: nArv < nDep \n";
                exit(1);
            }
        }
        else
        {
            Packet* packet = dynamic_cast<Packet*>(event);
            
            if(packet->type() == Arrival)
            {
                nArv++;
                E_T -= packet->arrivalTime();
            }
            else
            {
                nDep++;
                E_T += packet->arrivalTime();
            }
        }

        delete event;
        eventQueue.pop_back();
    }
    
    E_T /= nDep;
    E_N /= nObs;
}

std::ostream& operator<<(std::ostream& output, const Stats& stats)
{
    output << "Simulation time: " << stats.simulationTime << " s\n";
    output << "-------------------------------\n";
    output << "nObs = " << stats.nObs << "\n";
    output << "nArv = " << stats.nArv << "\n";
    output << "nDep = " << stats.nDep << "\n";
    output << "PIdle = " << stats.nIdle*1.0/stats.nObs << "\n";
    output << "E_T = " << stats.E_T << "\n";
    output << "E_N = " << stats.E_N << "\n";
    
    return output;
}
    
} // namespace lab1
