#pragma once
#include "aabb.h"
#include "triangle.h"
#include "ray.h"
#include <vector>
using namespace std;
struct KDNode
{
	//��ǰ�ڵ�����������ε�ָ��
	vector<Triangle*> triangles;
	//��Χ�У���ΧKD�ڵ����е�������
	AABB  aabb;
	KDNode* left;
	KDNode* right;
	KDNode(vector<Triangle*> tris = vector<Triangle*>(),AABB boundingBox = AABB(), KDNode* l = nullptr, KDNode* r = nullptr) :
		triangles(tris),aabb(boundingBox), left(l), right(r)
	{};
};
class KDTree
{
private:
	KDNode* root;
	KDNode* buildTree(vector<Triangle*> & tris, int depth) const;
	void Collide(KDNode* t,Ray& ray, Crash& crashResult);
	void makeEmpty(KDNode* &t);
public:
	KDTree()
	{
		root = nullptr;
	}
	KDTree(vector<Triangle*>& triangles)
	{
		root = buildTree(triangles, 0);
	}
	void Build(vector<Triangle*>& triangles);
	~KDTree();
	void Collide(Ray& ray,Crash& crashResult);
};