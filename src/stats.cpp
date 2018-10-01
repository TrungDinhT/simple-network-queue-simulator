// Local include
#include "stats.h"

// System include
#include <iostream>
#include <climits>
#include <algorithm>

namespace lab1
{

Stats::Stats()
:   nObs(0),
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

void Stats::process(std::vector<Event*>& eventQueue, unsigned long queueLength, double simulationTime)
{
    double              nextDeparture = 0.0;
    std::deque<double>  nextDepartures;
    
    while(!eventQueue.empty())
    {
        Event* event = eventQueue.back();
        double currentTime = event->arrivalTime();

        /*
         * This is useless when the buffer is infinite, since we don't push anything
         * in nextDepartures deck.
         * In case that the buffer is finite, this one will update nDep and nextDepartures
         * each time we meet an event.
         */
        processDepartureQueue(nextDepartures, currentTime);
        
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
                finiteQueuePacketStats(packet, queueLength,
                                       currentTime, simulationTime,
                                       nextDepartures, nextDeparture);
            }
        }

        delete event;
        eventQueue.pop_back();
    }
    
    E_T /= nDep;
    E_N /= nObs;
}

void Stats::processDepartureQueue(std::deque<double>& nextDepartures, double currentTime)
{
    while(!nextDepartures.empty() && currentTime >= nextDepartures.front())
    {
        nDep++;
        E_T += nextDepartures.front();
        nextDepartures.pop_front();
        //         std::cout << "currentTime = " << currentTime*1000 << " ms\n";
        //         std::cout << "nextDeparture = " << nextDeparture*1000 << " ms\n";
    }
}

void Stats::observerStats()
{
    nObs++;
    
    if(nArv > nDep)
    {
        E_N += nArv - nDep - nLoss;
    }
    else if(nArv == nDep + nLoss)
    {
        nIdle++;
    }
    else
    {
        std::cerr << "ERROR: nArv = " << nArv << " < nDep" << nDep << "\n";
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

void Stats::finiteQueuePacketStats(const Packet* packet, unsigned long queueLength, 
                                   double currentTime, double simulationTime,
                                   std::deque<double>& nextDepartures, double& nextDeparture)
{
    nArv++;

    if((nArv - nLoss - nDep) == queueLength + 1) // queue full
    {
        nLoss++;
    }
    else if ((nArv - nLoss - nDep) <= queueLength) // queue not full yet
    {
        double departureTime;
        double serviceTime = packet->packetSize()/C;

        if(currentTime >= nextDeparture)
        {
            departureTime = currentTime + serviceTime;
        }
        else
        {
            departureTime = nextDeparture + serviceTime;
        }
        
        if(departureTime <= simulationTime)
        {
            nextDepartures.push_back(departureTime);
            std::sort(nextDepartures.begin(), nextDepartures.end());
            
            E_T -= currentTime;
            
            // Update departure with the latest one
            nextDeparture = nextDepartures.back();
        }
        else
        {
            // Pretending that packet never exists
            nArv--;
        }
    }
    else
    {
        std::cerr << "ERROR: nArv = " << nArv << ", nDep = " << nDep << ", nLoss= " << nLoss << "\n";
        exit(1);
    }
}

std::ostream& operator<<(std::ostream& output, const Stats& stats)
{
    output << stats.nObs << ",";
    output << stats.nArv << ",";
    output << stats.nDep << ",";
    output << stats.nIdle*100.0/stats.nObs << ",";
    output << stats.nLoss*100.0/stats.nArv << ",";
    output << stats.E_N << ",";
    output << stats.E_T << "\n";
    
    return output;
}

} // namespace lab1
