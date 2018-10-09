#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Define global parameters
#define N 1000
#define lambda 75

double randValue()
{
    return log(1 - rand()*1.0/RAND_MAX)*-1.0/lambda;
}

int main()
{
    unsigned int i;
    double randomValues[N];
    double mean = 0, var = 0;

    srand(time(NULL));
    for(i=0; i < N; i++)
    {
        double val = randValue();
        randomValues[i] = val;    
        mean += val;
        var  += val*val; 
    }

    mean /= N;
    var   = var/N - mean*mean;

    printf("Mean of %d random numbers (expected %f) = %f\n", N, 1.0/lambda, mean);
    printf("Variance of %d random numbers (expected %f) = %f\n", N, 1.0/(lambda*lambda), var);

    return 0;
}
