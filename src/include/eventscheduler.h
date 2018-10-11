#ifndef EVENT_SCHEDULER_H
#define EVENT_SCHEDULER_H

// Local include
#include "stats.h"
#include "event.h"

// System include
#include <iostream>
#include <vector>

namespace lab1
{

// This class should be a singleton
class EventScheduler
{
public:
    EventScheduler();
    ~EventScheduler();
    
    void         init(double simulationTime, double rho);
    const Stats& getStats(unsigned long queueLength, double simulationTime);

private:
    void         initArrival(double simulationTime, double lambda);
    void         initObserver(double simulationTime, double alpha);
    void         initDeparture(double simulationTime);    

private:
    Stats               stats;
    std::vector<Event*> eventQueue;
    
    friend std::ostream& operator<<(std::ostream& output, const EventScheduler* ES);
};
    
} // namespace lab1

#endif // EVENT_SCHEDULER_H
