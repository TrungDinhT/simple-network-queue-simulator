// local includes
#include "eventscheduler.h"
#include "random.h"

// System includes
#include <algorithm>
#include <climits>

namespace lab1
{

bool compareEvent (const Event* e1, const Event* e2)
{
    return e1->arrivalTime() > e2->arrivalTime();
}

EventScheduler::EventScheduler()
{
}

EventScheduler::~EventScheduler()
{
    while(!eventQueue.empty())
    {
        eventQueue.pop_back();
    }
}

void EventScheduler::initObserver(double simulationTime, double alpha)
{
    // First observer should not be at 0
    double arrivalTime = Random::getInstance().randValue(alpha);
    
    Random::seedRand();
    
    do
    {
        Observer* event = new Observer(arrivalTime);
        eventQueue.push_back(event);
        arrivalTime += Random::getInstance().randValue(alpha);
    }
    while(arrivalTime <= simulationTime);    
}

void EventScheduler::initArrival(double simulationTime, double lambda)
{
    double arrivalTime = 0;    
    Random::seedRand();
    
    do
    {
        Packet* packet = new Packet(Arrival, arrivalTime, Random::getInstance().randValue(1.0/L));
        eventQueue.push_back(packet);
        arrivalTime += Random::getInstance().randValue(lambda);
    }
    while(arrivalTime < simulationTime);
}

void EventScheduler::initDeparture(double simulationTime)
{
    unsigned long   arrivalPos = 0;
    double          latestDeparture = 0;

    Packet*         arrival = dynamic_cast<Packet*>(eventQueue[arrivalPos]);
    
    do
    {
        Packet* packet;
        double  serviceTime, departureTime;

        serviceTime = arrival->packetSize()/C;
        
        if(arrival->arrivalTime() >= latestDeparture)
        {
            departureTime = arrival->arrivalTime() + serviceTime;
        }
        else
        {
            departureTime = latestDeparture + serviceTime;
        }
        
        if(departureTime <= simulationTime)
        {
            packet = new Packet(Departure, departureTime, arrival->packetSize());            
            latestDeparture = departureTime;
        }
        else
        {
            /* Here this packet depart after the simulation ends, so we will not count this packet among the arrival packets
             * One way to do is to SET arrivalTime of arrival pakcets TO departureTime, which is > simulationTime. In addition, we don't
             * modify latestDeparture.
             * 
             * Further analysis in stat.cpp will help us remove these packets out of our concerned packets.
             */
            arrival->setArrivalTime(departureTime);
            packet = new Packet(Departure, departureTime, arrival->packetSize());
        }
        
        eventQueue.push_back(packet);

        arrivalPos++;
        
        arrival = dynamic_cast<Packet*>(eventQueue[arrivalPos]);
    }
    while(arrival != nullptr);
}

void EventScheduler::init(double simulationTime, double rho)
{
    initArrival(simulationTime, rho*C/L);
    initObserver(simulationTime, 4*rho*C/L); //alpha = 4*lambda

    // Infinite queue
#ifdef infQueue
    initDeparture(simulationTime);
#endif
    
    // Sort events following time order
    std::sort(eventQueue.begin(), eventQueue.end(), compareEvent);
}

const Stats& EventScheduler::getStats(unsigned long queueLength, double simulationTime)
{
    stats.process(eventQueue, queueLength, simulationTime);
    return stats;
}

std::ostream& operator<<(std::ostream& output, const EventScheduler* ES)
{
    for(unsigned i = 0; i < ES->eventQueue.size(); i++)
    {
        output << ES->eventQueue[i] << "\n";
    }
    
    return output;
}
    
} // namespace lab1
