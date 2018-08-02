#include "polyhedron.h"

Crash Polyhedron::Collide(Ray ray) const
{
	ray.direction = ray.direction.GetUnitVector();
	Crash crash;
	kdtree.Collide(ray, crash);
	return crash;
}
Polyhedron::Polyhedron(std::string filename, Vector3 rotation,Vector3 offset, double scale)
{
	triangles = std::move(SimpleObjReader::ReadObjFile(filename, offset, scale));
	vector<Primitive*> p_triangles(triangles.size(), nullptr);
	barycentre = Vector3();
	for (unsigned int i = 0; i < triangles.size(); ++i)
	{
		p_triangles[i] = &triangles[i];
		barycentre += triangles[i].GetBarycentre() / double(triangles.size());
	}
	kdtree.BuildTree(&p_triangles);
}
AABB Polyhedron::GetAABB() const
{
	AABB ans = triangles[0].GetAABB();
	for (unsigned int i = 1; i < triangles.size(); ++i)
		ans.Extend(triangles[i].GetAABB());
	return ans;
}
