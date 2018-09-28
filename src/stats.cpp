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
    double currentTime;

    std::queue<double> nextDepartures;
    nextDepartures.push(0.0); // first packet arrived at 0

    this->queueLength = queueLength;
    
    while(!eventQueue.empty())
    {
        Event* event = eventQueue.back();

        currentTime = event->arrivalTime(); // = 0 == nextDeparture for first packet

        if(event->evtType() == Obs)
        {
            observerStats();    
        }
        else
        {
            Packet* packet = dynamic_cast<Packet*>(event);
            
            if(queueLength == ULONG_MAX) // Infinite queue
            {
                infiniteQueuePacketStats(packet);
            }
            else
            {
                /*
                * Every packet is arrival here. 
                */
                finiteQueuePacketStats(packet, currentTime, nextDepartures);
            }
        }

        delete event;
        eventQueue.pop_back();
    }
    
    E_T /= nDep;
    E_N /= nObs;
}

void Stats::observerStats()
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

void Stats::infiniteQueuePacketStats(const Packet* packet)
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

void Stats::finiteQueuePacketStats(const Packet* packet, double& currentTime, std::queue<double>& nextDepartures)
{
    double nextDeparture;

    while(currentTime > nextDeparture)
    {
        nextDeparture = nextDepartures.front();
        nextDepartures.pop();
        nDep++;
        E_T += nextDeparture;
    }

    if((nArv - nDep) == queueLength) // queue full
    {
        nLoss++;
    }
    else // (nArv - nDep) < queueLength -> queue not full yet
    {
        nArv++;
        E_T -= packet->arrivalTime();

        if(packet->arrivalTime() + serviceTime >= nextDeparture + serviceTime)
        {
            nextDepartures.push(packet->arrivalTime() + packet->packetSize()/C);
        }
        else
        {
            nextDepartures.push(nextDeparture + packet->packetSize()/C);
        }
    }
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
