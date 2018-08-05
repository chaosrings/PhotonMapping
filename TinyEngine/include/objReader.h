#pragma once
#include "vector3.h"
#include "triangle.h"
#include <vector>
#include <string>
#include <fstream>
using std::vector;
using std::string;
using std::fstream;
class SimpleObjReader
{
public:
	static vector<string>  SplitString(const string& target, char splitCh);
	static Vector3 ReadOneVertex(const vector<string>& curElements);
	static Triangle ReadOneTriangle(const vector<string>& curElements,
		const vector<Vector3>& vertices, const vector<Vector3>& textures,const vector<Vector3>& normals, Vector3 rotation,Vector3 offset, double scale);
	static  vector<Triangle> ReadObjFile(string filepath, Vector3 rotation,Vector3 offset,double scale);
	static vector<Triangle>  ReadObjEx(string filepath, Vector3 offset, double scale);
};