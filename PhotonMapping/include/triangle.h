#pragma once
#include "primitive.h"
#include "vector3.h"
#include "aabb.h"
#include "ray.h"
class Triangle : public Primitive
{
public:
	Vector3 vertex0;
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 normal;
	Vector3 barycentre;
	Triangle(Vector3 v0 = Vector3(), Vector3 v1 = Vector3(), Vector3 v2= Vector3()) :Primitive(),
		vertex0(v0), vertex1(v1), vertex2(v2)
	{
		//法向量是两边向量的叉积
		normal = ((v1 - v0)*(v2 - v0)).GetUnitVector();
		barycentre = (v0+v1+v2) /3.f;
	}
	AABB GetAABB();
	Crash Collide(Ray ray);
};