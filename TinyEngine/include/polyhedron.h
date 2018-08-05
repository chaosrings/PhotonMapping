#pragma once
#include "primitive.h"
#include "objReader.h"
#include "kdtree.h"
#include <iostream>
class Polyhedron : public Primitive
{
private:
	vector<Triangle> triangles;
	KDTree kdtree;
	Vector3 barycentre;
public:
	Polyhedron(std::string filename, Vector3 rotation,Vector3 offset, double scale);
	AABB GetAABB() const;
	Vector3 GetBarycentre() const { return barycentre; }
	Collide Intersect(Ray ray) const;
	int GetTriangleNum() { return triangles.size(); }
};