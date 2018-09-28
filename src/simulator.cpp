#include "simulator.h"
#include <iostream>


namespace lab1
{
    
Simulator::Simulator()
  : ES(0)
{
}

Simulator::~Simulator()
{
    if(ES)
    {
        delete ES;
    }
}

void Simulator::init(double rho)
{
    ES = new EventScheduler(rho);
    ES->init();
}

void Simulator::process()
{
    ES->getStats();
}

void Simulator::run()
{
    for(double rho = 0.25; rho <= 0.95; rho += 0.1)
    {
        init(rho);
//         std::cout << ES;
        
        process();
    }
}
    
} // namespace lab1



