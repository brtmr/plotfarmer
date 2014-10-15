#include"MyMath.h"

namespace mymath
{

void boundsInt(int *x, int lower, int upper)
{
    if ((*x) > upper)
    {
        *x = upper;
        return;
    }
    if ((*x) < lower)
    {
        *x = lower;
        return;
    }
}

void boundsFloat(float *x, float lower, float upper)
{
    if ((*x) > upper)
    {
        *x = upper;
        return;
    }
    if ((*x) < lower)
    {
        *x = lower;
        return;
    }
}

}
