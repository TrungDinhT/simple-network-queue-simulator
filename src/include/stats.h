#ifndef STATS_H
#define STATS_H

// Local include
#include "event.h"

// System include
#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

namespace lab1
{

class Stats
{
public:
    Stats();
    ~Stats();

    void process(std::vector<Event*>& eventQueue, unsigned long queueLength, double simulationTime);
    void print();

private:
    void processDepartureQueue(std::deque<double>& nextDepartures, double currentTime);
    void observerStats();
    void infiniteQueuePacketStats(const Packet* packet, double simulationTime);
    void finiteQueuePacketStats(const Packet* packet, unsigned long queueLength, 
                                double currentTime, double simulationTime,
                                std::deque<double>& nextDepartures, double& nextDeparture);    

private:
    unsigned long   nObs;
    unsigned long   nArv;
    unsigned long   nDep;
    unsigned long   nIdle;
    unsigned long   nLoss;
    double          E_T;
    double          E_N;

    friend std::ofstream& operator<<(std::ofstream& output, const Stats& stats);
};    
    
} // namespace lab1

#endif // STATS_H
