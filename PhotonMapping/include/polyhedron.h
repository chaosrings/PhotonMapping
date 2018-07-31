#pragma once
#include "primitive.h"
#include "objReader.h"
#include "KDTree.h"

class Polyhedron : public Primitive
{
private:
	//Matrix worldMat
	vector<Triangle> triangles;
	KDTree kdtree;
public:
	Polyhedron(std::string filename,Vector3 offset,double scale)
	{
		triangles = std::move(SimpleObjReader::ReadObjFile(filename));
		for (auto& triangle : triangles)
		{
			triangle.vertex0 *= scale;
			triangle.vertex1 *= scale;
			triangle.vertex2 *= scale;
			triangle.vertex0 += offset;
			triangle.vertex1 += offset;
			triangle.vertex2 += offset;
		}
		vector<Triangle*> p_triangles(triangles.size(), nullptr);
		for (int i = 0; i < triangles.size(); ++i)
		{
			p_triangles[i] = &triangles[i];
		}
		kdtree.Build(p_triangles);
	}
	Crash Collide(Ray ray);
};