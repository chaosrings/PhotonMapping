#include "common.h"
const float EPS= 1e-6;
const float PI= 3.1415926535897932384626;
std::default_random_engine e(time(nullptr));
std::uniform_real_distribution<float> u(0, 1);

const int maxEmitPhoton = 1000000;
const int maxPhotonTracingDepth = 10;
const int maxRayTracingDepth = 10;