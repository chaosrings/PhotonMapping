#include "primitive.h"

Crash  Sphere::Collide(Vector3 &origin, Vector3& direction)
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
	if (crash.front == false) crash.normal = -crash.normal;
	return crash;
}