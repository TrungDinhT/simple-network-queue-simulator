// Local include
#include "stats.h"

// System include
#include <iostream>
#include <climits>

namespace lab1
{

Stats::Stats(unsigned int T)
:   simulationTime(T),
    queueLength(0),
    nObs(0),
    nArv(0),
    nDep(0),
    nIdle(0),
    nLoss(0),
    E_T(0.0),
    E_N(0.0)
{
}

Stats::~Stats()
{
}

void Stats::process(std::vector<Event*>& eventQueue, unsigned long queueLength)
{
    this->queueLength = queueLength;
    
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
            double  latestDeparture = 0;
            
            if(queueLength == ULONG_MAX)
            {
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
            else
            {
                if((nArv - nDep) == queueLength)
                {
                    nLoss++;
                }
                else
                {
                    double serviceTime, departureTime;
                    
                    serviceTime = arrival->packetSize()/C;
                    
                    if(arrival->arrivalTime() + serviceTime >= latestDeparture + serviceTime)
                    {
                        departureTime = arrival->arrivalTime() + serviceTime;
                    }
                    else
                    {
                        departureTime = latestDeparture + serviceTime;
                    }
                }
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
    (stats.queueLength == ULONG_MAX)  
        ?   output << "queueLength = Inf \n" 
        :   output << "queueLength = " <<  queueLength << "\n";
    output << "-------------------------------\n";
    output << "nObs = " << stats.nObs << "\n";
    output << "nArv = " << stats.nArv << "\n";
    output << "nDep = " << stats.nDep << "\n";
    output << "PIdle = " << stats.nIdle*100.0/stats.nObs << "%\n";
    output << "PLoss = " << stats.nLoss*100.0/stats.nArv << "%\n"; 
    output << "E_T = " << stats.E_T << "\n";
    output << "E_N = " << stats.E_N << "\n";
    
    return output;
}
    
} // namespace lab1
