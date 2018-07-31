#include "polyhedron.h"

Crash Polyhedron::Collide(Ray ray)
{
	ray.direction = ray.direction.GetUnitVector();
	Crash crash;
	kdtree.Collide(ray, crash);
	return crash;
}
