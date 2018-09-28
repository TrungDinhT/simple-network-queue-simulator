#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "eventscheduler.h"

namespace lab1
{

class Simulator
{
public:
    Simulator();
    ~Simulator();

    void init(double rho);
    void process();
    
    void run();

private:
    EventScheduler* ES;
};
    
    
} // namespace lab1

#endif // SIMULATOR_H
