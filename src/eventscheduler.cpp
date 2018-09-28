// local includes
#include "eventscheduler.h"
#include "random.h"

// System includes
#include <algorithm>

// Total simulation time (in s)
#define simulationTime 10000

// Packet relevant parameters
#define lambda rho*C/L
#define L 12000
#define C 1000000

// Average observer per second
#define alpha 4*lambda

namespace lab1
{

bool compareEvent (const Event* e1, const Event* e2)
{
    return e1->arrivalTime() > e2->arrivalTime();
}

EventScheduler::EventScheduler(double rho)
  : rho(rho),
    stats(simulationTime)
{
}

EventScheduler::~EventScheduler()
{
    while(!eventQueue.empty())
    {
        eventQueue.pop_back();
    }
}

void EventScheduler::initObserver()
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
    while(arrivalTime < simulationTime);    
}

void EventScheduler::initPackets()
{
    std::vector<Packet*> packetQueue;

    initArrival(packetQueue);
    initDeparture(packetQueue);

    eventQueue.insert(eventQueue.end(), packetQueue.begin(), packetQueue.end());
}

void EventScheduler::initArrival(std::vector<Packet*>& packetQueue)
{
    double arrivalTime = 0;    
    Random::seedRand();
    
    do
    {
        Packet* packet = new Packet(Arrival, arrivalTime, Random::getInstance().randValue(1.0/L));
        packetQueue.push_back(packet);
        arrivalTime += Random::getInstance().randValue(lambda);
    }
    while(arrivalTime < simulationTime);
}

void EventScheduler::initDeparture(std::vector<Packet*>& packetQueue)
{
    unsigned long   arrivalPos = 0;
    double          latestDeparture = 0, serviceTime;

    Packet*         arrival = packetQueue[arrivalPos];
    PacketType      nextPacket;
    
    do
    {
        Packet* packet;
        double  departureTime;

        serviceTime = arrival->packetSize()/C;
        
        if(arrival->arrivalTime() + serviceTime >= latestDeparture + serviceTime)
        {
            departureTime = arrival->arrivalTime() + serviceTime;
        }
        else
        {
            departureTime = latestDeparture + serviceTime;
        }
        
        packet = new Packet(Departure, departureTime, arrival->packetSize());
        packetQueue.push_back(packet);
        
        latestDeparture = departureTime;
        arrivalPos++;
        
        arrival = packetQueue[arrivalPos];
    }
    while(arrival->type() == Arrival);
}

void EventScheduler::init()
{
    unsigned long firstArrivalPacketPosition;

    initObserver();
    initPackets();
    
    // Sort events following time order
    std::sort(eventQueue.begin(), eventQueue.end(), compareEvent);
}

void EventScheduler::getStats()
{
    stats.process(eventQueue);
    
    std::cout << "******************************************************\n";
    std::cout << "rho = " << rho << "\n";
    std::cout << stats;
    std::cout << "******************************************************\n";
    std::cout << "\n";
}

std::ostream& operator<<(std::ostream& output, const EventScheduler* ES)
{
    for(int i = 0; i < ES->eventQueue.size(); i++)
    {
        output << ES->eventQueue[i] << "\n";
    }
    
    return output;
}
    
} // namespace lab1
