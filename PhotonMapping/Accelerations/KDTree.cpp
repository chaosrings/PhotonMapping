#include "KDTree.h"
#include <algorithm>

AABB KDTree::GetBoundingBox(const vector<Triangle*>& tris)
{
	AABB res = tris[0]->GetAABB();
	for (unsigned int i = 1; i < tris.size(); ++i)
		res.Extend(tris[i]->GetAABB());
	return res;
}

//tris为三角形vector的指针的原因是在堆上分配内存防止stack overflow
//若为vector<Triangle*> &tris可能溢出
KDNode* KDTree::buildTree(vector<Triangle*>* tris, int depth)
{	
	if (depth > height)
		height = depth;
	
	//拷贝赋值
	KDNode* node = new KDNode(*tris);
	//包围盒
	node->aabb = GetBoundingBox(*tris);
	if (tris->size() == 1)
		return node;
	Vector3 midPoint = Vector3(0, 0, 0);
	//以三角形重心为划分标准,小于在左，大于在右
	for (auto ptriangle : *tris)
		midPoint += (ptriangle->barycentre / double(tris->size()));
	auto left_tris=new vector<Triangle*>();
	auto right_tris= new vector<Triangle*>();
	int splitAxis = node->aabb.GetLongestAxis();
	for (auto ptriangle :*tris)
	{
		if (ptriangle->barycentre.GetCoord(splitAxis) < midPoint.GetCoord(splitAxis))
			left_tris->push_back(ptriangle);
		else
			right_tris->push_back(ptriangle);
	}
	//若平均重心无法分离，子节点直接构造
	if (left_tris->size() == 0)
		node->right = new KDNode(*right_tris,GetBoundingBox(*right_tris));
	else if (right_tris->size() == 0)
		node->left = new KDNode(*left_tris, GetBoundingBox(*left_tris));
	else
	{
		//否则继续划分
		node->left = buildTree(left_tris, depth + 1);
		node->right = buildTree(right_tris, depth + 1);
	}
	delete left_tris;
	delete right_tris;
	return node;
}

void KDTree::Collide(KDNode* node,Ray& ray, Crash& crashResult)
{
	if (node->aabb.Hit(ray))
	{
		//到达叶节点
		if (node->left == nullptr&&node->right == nullptr)
		{
			double minDist = INF;
			for (auto ptriangle : node->triangles)
			{
				Crash curCrash = ptriangle->Collide(ray);
				if (curCrash.crashed&&curCrash.dist < minDist)
					crashResult = curCrash;
			}
		}
		else
		{
			if (node->left != nullptr)
				Collide(node->left, ray, crashResult);
			if (node->right != nullptr)
				Collide(node->right, ray, crashResult);
		}
	}
}

void KDTree::Collide(Ray& ray, Crash& crashResult)
{
	Collide(root, ray, crashResult);
}
void KDTree::makeEmpty(KDNode* &t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}
void KDTree::Build(vector<Triangle*>* triangles)
{
	makeEmpty(root);
	root = buildTree(triangles, 0);
}
KDTree::~KDTree()
{
	makeEmpty(root);
}