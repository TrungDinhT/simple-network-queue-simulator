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
    EventScheduler(double rho);
    ~EventScheduler();
        
    void    initArrival();
    void    initObserver();
    void    initDeparture();
    
    void    init();
    void    getStats();

private:
    double               rho;
    Stats                stats;
    std::vector<Event*>  eventQueue;
    
    friend std::ostream& operator<<(std::ostream& output, const EventScheduler* ES);
};
    
} // namespace lab1

#endif // EVENT_SCHEDULER_H
