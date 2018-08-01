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
public:
	Polyhedron(std::string filename,Vector3 offset,double scale)
	{
		triangles = std::move(SimpleObjReader::ReadObjFile(filename,offset,scale));
		vector<Triangle*> p_triangles(triangles.size(), nullptr);
		for (unsigned int i = 0; i < triangles.size(); ++i)
		{
			p_triangles[i] = &triangles[i];
		}
		kdtree.Build(&p_triangles);
		std::cout << kdtree.GetHeight() <<std::endl;
	}
	Crash Collide(Ray ray);
};