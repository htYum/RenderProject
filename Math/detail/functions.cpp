#include "functions.h"

const float PI = 3.1415926;

float angles(float radians)
{
    return radians*180/PI;
}

float radians(float angle)
{
    return angle*PI/180;
}
