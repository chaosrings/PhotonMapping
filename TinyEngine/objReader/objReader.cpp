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
	if(curElements.size()==4)
		return Vector3(std::stod(curElements[1]), std::stod(curElements[2]), std::stod(curElements[3]));
	return Vector3(std::stod(curElements[1]), std::stod(curElements[2]),0);
}
Triangle inline SimpleObjReader::ReadOneTriangle(const vector<string>& curElements, 
	const vector<Vector3>& vertices, const vector<Vector3>& textures, const vector<Vector3>& normals,
	Vector3 rotation,Vector3 offset,double scale)
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
	auto v1 = vertices[vertexIndex[0]];
	auto v2 = vertices[vertexIndex[1]];
	auto v3 = vertices[vertexIndex[2]];
	//顶点坐标先旋转
	for (int i = 0; i < 3; ++i)
	{
		v1 = v1.RotateWithAxis(i, rotation.GetCoord(i)*PI / 180);
		v2 = v2.RotateWithAxis(i, rotation.GetCoord(i)*PI / 180);
		v3 = v3.RotateWithAxis(i, rotation.GetCoord(i)*PI / 180);
	}
	//再放缩，偏移
	ans = Triangle(v1* scale + offset, v2 * scale + offset, v3 * scale + offset);
	ans.normal = (ans.vertex[1] - ans.vertex[0])*(ans.vertex[2] - ans.vertex[0]);
	if (ans.normal.IsZeroVector())
		ans.normal = Vector3(0, 0, 1);
	else
		ans.normal = ans.normal.GetUnitVector();
	//将三角形三个顶点的法向量,纹理坐标赋予正确的值
	for (int i = 0; i < 3; ++i)
	{
		ans.vertexNormals[i] = (normalIndex[i] != -1) ? normals[normalIndex[i]] : ans.normal;
		//法向量旋转
		if (normalIndex[i] != -1)
		{
			for(int j=0;j<3;++j)
			{
				ans.vertexNormals[i] = ans.vertexNormals[i].RotateWithAxis(j, rotation.GetCoord(j)*PI / 180);
			}
			
		}
		//纹理坐标
		ans.vertexTexutures[i] = (textureIndex[i] != -1) ? textures[textureIndex[i]] : Vector3(0,0,0);
	}
	//重心
	ans.barycentre = (ans.vertex[0] + ans.vertex[1] + ans.vertex[2]) / 3;
	return ans;
}
vector<Triangle> SimpleObjReader::ReadObjFile(string filepath, Vector3 rotation,Vector3 offset,double scale)
{
	vector<Triangle> tris;
	vector<Vector3>  vertices(1,Vector3());
	vector<Vector3>  textures(1, Vector3());
	vector<Vector3>  normals(1, Vector3());
	std::ifstream ifs;
	ifs.open(filepath);
	if (!ifs)
		throw std::exception("file doesn't exist");
	string curLine;
	vector<string> curElements;
	while (std::getline(ifs, curLine))
	{
		curElements = std::move(SplitString(curLine, ' '));
		if (curElements.size()==0||curElements[0] == "#")
			continue;
		if (curElements[0] == "v")
			vertices.push_back(ReadOneVertex(curElements));
		if (curElements[0] == "vt")
			textures.push_back(ReadOneVertex(curElements));
		if (curElements[0] == "vn")
			normals.push_back(ReadOneVertex(curElements));
		if (curElements[0] == "f")
			tris.push_back(ReadOneTriangle(curElements,vertices,textures,normals,rotation,offset,scale));
	}
	return tris;
	
}
