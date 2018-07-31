#pragma once
#include <random>
#include <time.h>
#include <assert.h>
extern const double EPS;
extern const double INF;
extern const double PI; 
extern std::default_random_engine e;
extern std::uniform_real_distribution<double> u;
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