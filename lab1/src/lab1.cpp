#include "../include/lab1.hpp"

int lab1_var17(int upSpeed, int downSpeed, int desiredHeight)
{
    int init = 0;
    int count = 0;
    
    while (init <= desiredHeight)
    {
        init += upSpeed;
        if (init >= desiredHeight)
        {
            count++;
            break;
        }
        init -= downSpeed;
        count++;
    }

    return count;
}
