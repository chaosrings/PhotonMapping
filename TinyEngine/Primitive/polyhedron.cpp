#include "polyhedron.h"

Collide Polyhedron::Intersect(Ray ray) const
{
	ray.direction = ray.direction.GetUnitVector();
	Collide collide;
	kdtree.Intersect(ray, collide);
	return collide;
}
Polyhedron::Polyhedron(std::string filename, Vector3 rotation,Vector3 offset, double scale)
{
	triangles = std::move(SimpleObjReader::ReadObjFile(filename, rotation,offset, scale));
	vector<Primitive*> p_triangles(triangles.size(), nullptr);
	barycentre = Vector3();
	//设置父节点，获取三角形的指针，预计算重心
	for (unsigned int i = 0; i < triangles.size(); ++i)
	{
		triangles[i].parent = this;
		p_triangles[i] = &triangles[i];
		barycentre += triangles[i].GetBarycentre() / double(triangles.size());
	}
	kdtree.BuildTree(&p_triangles);
}
AABB Polyhedron::GetAABB() const
{
	return kdtree.BoundingBox();
}
