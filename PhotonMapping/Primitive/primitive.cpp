#include "primitive.h"

Crash Plane::Collide(Vector3 origin, Vector3 direction)
{
	Crash crash;
	direction = direction.GetUnitVector();
	normal = normal.GetUnitVector();
	float t1 = normal.Dot(center - origin);
	if (t1 > EPS)   //与0比较为何不可？
		crash.front = false;
	else
		crash.front = true;
	float t2 = direction.Dot(normal);
	float t = t1 / t2;
	if (t <EPS)	//与0比较为何不可？
	{
		crash.crashed = false;
		return crash;
	}
	crash.position = origin + direction*t;
	crash.dist = t;
	if (crash.position.Distance2(center)>halfLength*halfLength+halfWidth*halfWidth)
	{
		crash.crashed = false;
		return crash;
	}
	crash.crashed = true;
	crash.normal = (crash.front) ? normal : -normal;
	return crash;
}

Color Plane::GetTexture(Vector3 pos)
{
		
}


Crash  Sphere::Collide(Vector3 origin, Vector3 direction)
{
	Crash crash;
	direction = direction.GetUnitVector();
	Vector3 P = origin - center;
	float b = -P.Dot(direction);
	float det = b * b - P.Module2() + radius * radius;

	if (det > EPS) {
		det = sqrt(det);
		float x1 = b - det, x2 = b + det;

		if (x2 < EPS) { crash.crashed = false; return crash; }
		crash.crashed = true;
		if (x1 > EPS) {
			crash.dist = x1;
			crash.front = true;
		}
		else {
			crash.dist = x2;
			crash.front = false;
		}
	}
	else
	{
		crash.crashed = false;
		return crash;
	}

	crash.position = origin + direction * crash.dist;
	crash.normal = (crash.position - center).GetUnitVector();
	if (crash.front == false)
		crash.normal = -crash.normal;
	return crash;
}

Color Sphere::GetTexture(Vector3 normal)
{
	normal = normal.GetUnitVector();
	float u = asin(normal.x) / PI + 0.5f;
	float v = asin(normal.y) / PI + 0.5f;
	return (this->material.texture)->GetSmoothColor(u, v);
}