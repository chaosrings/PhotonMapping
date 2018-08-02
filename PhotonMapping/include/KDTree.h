#pragma once
#include "aabb.h"
#include "triangle.h"
#include "ray.h"
#include <vector>
using namespace std;
struct KDNode
{
	//当前节点包含基本体的指针
	vector<Primitive*> primitives;
	//包围盒，包围KD节点所有的三角形
	AABB  aabb;
	KDNode* left;
	KDNode* right;
	KDNode(vector<Primitive*> prims = vector<Primitive*>(),AABB boundingBox = AABB(), KDNode* l = nullptr, KDNode* r = nullptr) :
		primitives(prims),aabb(boundingBox), left(l), right(r)
	{};
};
class KDTree
{
private:
	int height;
	KDNode* root;
	KDNode* BuildTree(vector<Primitive*> * tris, int depth);
	void Intersect(KDNode* t,Ray& ray, Collide& crashResult) const;
	void makeEmpty(KDNode*& t);
public:
	
	KDTree(){height = 0;root = nullptr;	}
	~KDTree();
	//禁止拷贝
	KDTree& operator=(const KDTree& rhs) = delete;
	void Clear() { makeEmpty(root); }
	AABB GetBoundingBox(const vector<Primitive*>& tris) const;
	int GetHeight() const { return height; } 
	void BuildTree(vector<Primitive*>* triangles);
	void Intersect(Ray& ray,Collide& crashResult)const ;
};