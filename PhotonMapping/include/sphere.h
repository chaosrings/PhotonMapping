#pragma once
#include "primitive.h"

class Sphere : public Primitive
{
private:
	Vector3 center;
	double radius;
public:
	Sphere(Vector3 _center = Vector3(), double _radius = 0.f) :Primitive(), center(_center), radius(_radius) {};
	~Sphere() {}

	Collide Intersect(Ray ray) const;
	AABB  GetAABB() const;

	void SetCenter(Vector3 _center) { center = _center; }
	void SetRadius(double r) { radius = r; }

	Vector3 GetCenter() const { return center; }
	Vector3 GetRadius() const { return radius; }
	Vector3 GetBarycentre() const { return center; }
	Color GetTexture(Collide) const;
	
};