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
	Vector3 vertexNormals[3];
	Triangle(Vector3 v0 = Vector3(), Vector3 v1 = Vector3(), Vector3 v2= Vector3()) :Primitive(),
		vertex0(v0), vertex1(v1), vertex2(v2){}
	AABB GetAABB() const;
	Crash Collide(Ray ray) const;
	Vector3 GetBarycentre() const { return barycentre; }
};