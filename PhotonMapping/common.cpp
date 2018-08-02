#include "common.h"

const double EPS= 0.00001;
const double PI= 3.1415926535897932384626;
const double INF = 10000000;
std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
std::uniform_real_distribution<double> u(0, 1);

const int maxEmitPhoton = 1000000;
const int maxPhotonTracingDepth = 20;
const int maxRayTracingDepth =20;