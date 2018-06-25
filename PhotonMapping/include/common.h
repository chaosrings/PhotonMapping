#pragma once
#include <random>
#include <time.h>
extern const float EPS; 
extern const float PI; 
extern std::default_random_engine e;
extern std::uniform_real_distribution<float> u;
extern const int maxEmitPhoton;
extern const int maxPhotonTracingDepth;
extern const int maxRayTracingDepth;

#define RandomRealZeroOne() (u(e))

template <typename T>
T clamp(T x,T minvalue,T maxvalue)
{
	if (x < minvalue)
		x = minvalue;
	else if (x > maxvalue)
		x = maxvalue;
	return x;
}