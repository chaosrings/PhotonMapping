#pragma once
#include "vector3.h"
class Ray
{
public:
	Vector3 origin;
	Vector3 direction;
	Ray(Vector3 _origin = Vector3(0, 0, 0), Vector3 _direction = Vector3(0, 0, 0)) :origin(_origin), direction(_direction) {}
	void rayDiff(Vector3 normal);
	void rayRefl(Vector3 normal);
	void rayRefr(Vector3 normal, double n);
	
};



