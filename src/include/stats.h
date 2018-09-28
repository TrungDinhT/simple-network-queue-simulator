#ifndef STATS_H
#define STATS_H

// Local include
#include "event.h"

// System include
#include <iostream>
#include <vector>
#include <queue>

namespace lab1
{

class Stats
{
public:
    Stats(unsigned int T);
    ~Stats();

    void process(std::vector<Event*>& eventQueue, unsigned long queueLength);

private:
    void observerStats();
    void infiniteQueuePacketStats(const Packet* packet);
    void finiteQueuePacketStats(const Packet* packet, double& currentTime, 
                                std::queue<double>& nextDepartures);    

private:
    unsigned int    simulationTime;
    unsigned long   queueLength;
    unsigned long   nObs;
    unsigned long   nArv;
    unsigned long   nDep;
    unsigned long   nIdle;
    unsigned long   nLoss;
    double          E_T;
    double          E_N;
    friend std::ostream& operator<<(std::ostream& output, const Stats& stats);
};    
    
} // namespace lab1

#endif // STATS_H
