#ifndef EVENT_H
#define EVENT_H

// System include
#include <iostream>

// Network parameters
#define L 12000
#define C 1000000

namespace lab1
{

enum EventType
{
    Obs = 0,
    Pkt
};

enum PacketType
{
    Arrival = 0,
    Departure
};

// ------------------------------------------------
    
class Event
{
public:
    Event(EventType type, double t);
    virtual ~Event();
    
    EventType   evtType() const;
    double      arrivalTime() const;
    void        setArrivalTime(double t);
    
    virtual std::ostream& print(std::ostream& output);

protected:
    EventType   type;
    double      arvTime;
    
    friend std::ostream& operator<<(std::ostream& output, Event* e);
};

// ------------------------------------------------

class Observer: public Event
{
public:
    Observer(double arrivalTime);
    ~Observer();
};

// ------------------------------------------------

class Packet: public Event
{
public:
    
    Packet(PacketType type, double arrivalTime, double l);
    ~Packet();
    
    double packetSize() const;
    PacketType type() const;
    
    std::ostream& print(std::ostream& output) override;

private:
    double     length;
    PacketType pktType;
};
    
} // namespace lab1

#endif // EVENT_H
