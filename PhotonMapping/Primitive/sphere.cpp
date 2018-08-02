#include "sphere.h"
Collide  Sphere::Intersect(Ray ray) const
{
	Collide collide;
	auto direction = ray.direction.GetUnitVector();
	auto origin = ray.origin;
	Vector3 P = origin - center;
	double b = -P.Dot(direction);
	double det = b * b - P.Module2() + radius * radius;

	if (det > EPS) {
		det = sqrt(det);
		double x1 = b - det, x2 = b + det;

		if (x2 < EPS) { collide.crashed = false; return collide; }
		collide.crashed = true;
		if (x1 > EPS) {
			collide.dist = x1;
			collide.front = true;
		}
		else {
			collide.dist = x2;
			collide.front = false;
		}
	}
	else
	{
		collide.crashed = false;
		return collide;
	}

	collide.position = origin + direction * collide.dist;
	collide.normal = (collide.position - center).GetUnitVector();
	if (collide.front == false)
		collide.normal = -collide.normal;
	return collide;
}

AABB Sphere::GetAABB() const
{
	AABB ans;
	ans.minCoord = Vector3(center.x - radius, center.y - radius, center.z - radius);
	ans.maxCoord = Vector3(center.x + radius, center.y + radius, center.z + radius);
	return ans;
}
//·¨ÏßÌùÍ¼
Color Sphere::GetTexture(Collide collide) const
{
	auto normal = collide.normal;
	normal = normal.GetUnitVector();
	double u = asin(normal.x) / PI + 0.5f;
	double v = asin(normal.y) / PI + 0.5f;
	return (this->material.texture)->GetSmoothColor(u, v);
}