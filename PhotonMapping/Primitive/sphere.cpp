#include "sphere.h"
Crash  Sphere::Collide(Ray ray)
{
	Crash crash;
	auto direction = ray.direction.GetUnitVector();
	auto origin = ray.origin;
	Vector3 P = origin - center;
	double b = -P.Dot(direction);
	double det = b * b - P.Module2() + radius * radius;

	if (det > EPS) {
		det = sqrt(det);
		double x1 = b - det, x2 = b + det;

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

Color Sphere::GetTexture(Crash crash)
{
	auto normal = crash.normal;
	normal = normal.GetUnitVector();
	double u = asin(normal.x) / PI + 0.5f;
	double v = asin(normal.y) / PI + 0.5f;
	return (this->material.texture)->GetSmoothColor(u, v);
}