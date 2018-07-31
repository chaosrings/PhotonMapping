#include "objReader.h"

vector<string> SimpleObjReader::SplitString(const string& target, char splitCh)
{
	vector<string> ans;
	string curElement = "";
	for (int i = 0; i < target.size(); ++i)
	{
		if (target[i] != splitCh)
			curElement += target[i];
		else
		{
			if(curElement.size()!=0)
				ans.push_back(curElement);
			curElement = "";
		}
	}
	if (curElement.size() != 0)
		ans.push_back(curElement);
	return ans;
}
Vector3 inline SimpleObjReader::ReadOneVertex(const vector<string>& curElements)
{
	assert(curElements[0] == "v");
	return Vector3(std::stod(curElements[1]), std::stod(curElements[2]), std::stod(curElements[3]));
}
Triangle inline SimpleObjReader::ReadOneTriangle(const vector<string>& curElements, const vector<Vector3>& vertices)
{
	assert(curElements[0] == "f");
	unsigned int v1Index = std::stoi(curElements[1]);
	unsigned int v2Index = std::stoi(curElements[2]);
	unsigned int v3Index = std::stoi(curElements[3]);
	return Triangle(vertices[v1Index], vertices[v2Index], vertices[v3Index]);
}
vector<Triangle> SimpleObjReader::ReadObjFile(string filepath)
{
	vector<Triangle> tris;
	vector<Vector3>  vertices;
	vertices.push_back(Vector3());
	std::ifstream ifs;
	ifs.open(filepath);
	if (!ifs)
	{
		throw std::exception("file doesn't exist");
	}
	string curLine;
	vector<string> curElements;
	while (std::getline(ifs, curLine))
	{
		curElements = std::move(SplitString(curLine, ' '));
		if (curElements[0] == "#")
			continue;
		if (curElements[0] == "v")
			vertices.push_back(ReadOneVertex(curElements));
		if (curElements[0] == "f")
			tris.push_back(ReadOneTriangle(curElements, vertices));
	}
	return tris;
	
}