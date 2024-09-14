#include "../include/lab1.h"

long long lab1_var17(long long upSpeed, long long downSpeed, long long desiredHeight)
{
    long long init = 0;
    int count = 0;
    
    while (init != desiredHeight)
    {
        init += upSpeed;
        init -= downSpeed;
        count++;
    }

    return count;
}
