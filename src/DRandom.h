#ifndef DRANDOM_H
#define DRANDOM_H

#include "irrlicht.h"

using namespace irr;
class DRandom
{

public:
     DRandom(unsigned long long int seed)
    {
        current = seed;
    }


    ~DRandom()
    {

    }

    float Get()
    {

        current = (a*current+c)%m;
        unsigned long long int output = (current / 131072)%2048;

        return output/2048.0;
    }

private:
    unsigned long current;
    static const unsigned long long int a = 1664525;
    static const unsigned long long int c = 1013904223;
    static const unsigned long long int m = 4294967296;




};

#endif // DRANDOM_H
