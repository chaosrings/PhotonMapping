#pragma once
#include "primitive.h"
#include "objReader.h"
#include "KDTree.h"
#include <iostream>
class Polyhedron : public Primitive
{
private:
	//Matrix worldMat
	vector<Triangle> triangles;
	KDTree kdtree;
	Vector3 barycentre;
public:
	Polyhedron(std::string filename, Vector3 rotation,Vector3 offset, double scale);
	AABB GetAABB() const;
	Vector3 GetBarycentre() const { return barycentre; }
	Crash Collide(Ray ray) const;
};