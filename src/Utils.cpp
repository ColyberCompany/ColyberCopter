/**
 * @file Utils.cpp
 * @author Jan Wielgus
 * @date 2021-08-18
 */

#include "Common/Utils.h"


float Common::Utils::invSqrt(float x)
{
    float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}


float Common::Utils::calculateAltitude(float p0, float p, float T_C)
{
	return (pow(p / p0, -0.19f) - 1) * (T_C + 273.15f)  * 153.846f;
}
