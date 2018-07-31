#pragma once
#include <algorithm>
#include "ray.h"
#include "common.h"

class AABB
{
public:
	AABB(Vector3 minC=Vector3(-INF,-INF,-INF), Vector3 maxC=Vector3(INF,INF,INF)):minCoord(minC),maxCoord(maxC){}
	bool Hit(Ray ray);
	void Extend(AABB another);
	int GetLongestAxis();
	Vector3 minCoord;
	Vector3 maxCoord;
};