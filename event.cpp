#include "event.h"


namespace lab1
{

Event::Event(EventType type, double t)
  : type(type),
    arvTime(t)
{
}

Event::~Event()
{
}

EventType Event::evtType() const
{
    return type;
}

double Event::arrivalTime() const
{
    return arvTime;
}

std::ostream& Event::print(std::ostream& output)
{
    if(type == Obs)
    {
        output << "Observer ";
    }
    output << arvTime*1000 << " ms";
    
    return output;
}

std::ostream& operator<<(std::ostream& output, Event* e)
{
    return e->print(output);
}

// ------------------------------------------------

Observer::Observer(double arrivalTime)
  : Event(Obs, arrivalTime)
{
}

Observer::~Observer()
{
}

// ------------------------------------------------

Packet::Packet(PacketType type, double arrivalTime, double l)
  : Event(Pkt, arrivalTime),
    length(l),
    pktType(type)
{
}

Packet::~Packet()
{
}

double Packet::packetSize() const
{
    return length;
}

PacketType Packet::type() const
{
    return pktType;
}

std::ostream& Packet::print(std::ostream& output)
{
    if(pktType == Arrival)
    {
        output << "Arrival ";
    }
    else
    {
        output << "Departure ";
    }
    output << arvTime*1000 << " ms; ";
    output << length << " bits";
    
    return output;
}

} // namespace lab1


