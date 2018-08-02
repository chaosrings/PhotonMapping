#include "objReader.h"

vector<string> SimpleObjReader::SplitString(const string& target, char splitCh)
{
	vector<string> ans;
	string curElement = "";
	for (unsigned int i = 0; i < target.size(); ++i)
	{
		if (target[i] != splitCh&&target[i]!='\n'&&target[i]!='\t'&&target[i]!=' ')
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
	return Vector3(std::stod(curElements[1]), std::stod(curElements[2]), std::stod(curElements[3]));
}
Triangle inline SimpleObjReader::ReadOneTriangle(const vector<string>& curElements, const vector<Vector3>& vertices,const vector<Vector3>& normals ,Vector3 offset,double scale)
{
	Triangle ans;
	int vertexIndex[3] = { -1,-1,-1};
	int textureIndex[3] = { -1,-1,-1 };
	int normalIndex[3] = { -1,-1,-1 };
	for (int i = 1; i <= 3; ++i)
	{
		vector<string> vertexElements;
		// 以'/'分离为 顶点/纹理/法线 坐标
		if(curElements[i].find("//")==string::npos)
			vertexElements= std::move(SplitString(curElements[i], '/'));
		else
		{
			//以'//'分离为 顶点/法线 坐标
			vertexElements.resize(2, "-1");
			int pos = curElements[i].find_first_of("/");
			vertexElements[0] = curElements[i].substr(0, pos);
			vertexElements[1] = curElements[i].substr(pos + 2);
		}
		vertexIndex[i-1] = std::stoi(vertexElements[0]);
		if (vertexElements.size() == 2)
			normalIndex[i-1] = std::stoi(vertexElements[1]);
		else if (vertexElements.size() == 3)
		{
			textureIndex[i-1] = std::stoi(vertexElements[1]);
			normalIndex[i-1] = std::stoi(vertexElements[2]);
		}
	}
	ans = Triangle(vertices[vertexIndex[0]] * scale + offset, vertices[vertexIndex[1]] * scale + offset, vertices[vertexIndex[2]] * scale + offset);
	ans.normal = (ans.vertex1 - ans.vertex0)*(ans.vertex2 - ans.vertex0);
	if (ans.normal.IsZeroVector())
		ans.normal = Vector3(0, 0, 1);
	else
		ans.normal = ans.normal.GetUnitVector();
	//将三角形三个顶点的法向量赋予正确的值
	for (int i = 0; i < 3; ++i)
		ans.vertexNormals[i]=(normalIndex[i]!=-1)?  normals[normalIndex[i]]:ans.normal;
	ans.barycentre = (ans.vertex0 + ans.vertex1 + ans.vertex2) / 3;
	return ans;
}
vector<Triangle> SimpleObjReader::ReadObjFile(string filepath,Vector3 offset,double scale)
{
	vector<Triangle> tris;
	vector<Vector3>  vertices;
	vector<Vector3>  normals;
	vertices.push_back(Vector3());
	normals.push_back(Vector3());
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
		if (curElements.size()==0||curElements[0] == "#")
			continue;
		if (curElements[0] == "v")
			vertices.push_back(ReadOneVertex(curElements));
		if (curElements[0] == "vn")
			normals.push_back(ReadOneVertex(curElements));
		if (curElements[0] == "f")
			tris.push_back(ReadOneTriangle(curElements, vertices,normals,offset,scale));
	}
	return tris;
	
}

vector<Triangle>  SimpleObjReader::ReadObjEx(string filepath, Vector3 offset, double scale)
{
	vector<Triangle> tris;
	vector<Vector3>  vertices;
	vertices.push_back(Vector3());
	std::ifstream ifs;
	ifs.open(filepath);
	assert(ifs);
	string line;
	while (std::getline(ifs, line))
	{
		std::stringstream ss(line);
		std::string var;
		if (!(ss >> var))
			continue;

	}
	return tris;
}