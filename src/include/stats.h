#ifndef STATS_H
#define STATS_H

// Local include
#include "event.h"

// System include
#include <iostream>
#include <vector>

namespace lab1
{

class Stats
{
public:
    Stats(unsigned int T);
    ~Stats();

    void process(std::vector<Event*>& eventQueue);

private:
    unsigned long   nObs;
    unsigned long   nArv;
    unsigned long   nDep;
    unsigned long   nIdle;
    double          E_T;
    double          E_N;
    unsigned int    simulationTime;
    friend std::ostream& operator<<(std::ostream& output, const Stats& stats);
};    
    
} // namespace lab1

#endif // STATS_H
