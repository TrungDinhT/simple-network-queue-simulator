#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace lab1
{

class Random
{
public:
    static Random& getInstance()
    {
        static Random instance;
        return instance;
    }
    
    static void seedRand()
    {
        // Seed rand function with current time
        srand(time(NULL));
    }
    
    double randValue(double lambda)
    {
        return log(1 - rand()*1.0/RAND_MAX)*-1.0/lambda;
    }

private:
    Random(){}

    // Prevent operator= and copy constructor
    Random(const Random &);
    void operator=(const Random&);
};

} // namespace lab1

#endif // RANDOM_h

