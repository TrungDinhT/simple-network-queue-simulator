#ifndef EVENT_H
#define EVENT_H

// System include
#include <iostream>

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
    ~Event();
    
    EventType   evtType() const;
    double      arrivalTime() const;
    
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
    
    virtual std::ostream& print(std::ostream& output);

private:
    double     length;
    PacketType pktType;
};
    
} // namespace lab1

#endif // EVENT_H
