#include "KDTree.h"
#include <algorithm>
KDNode* KDTree::buildTree(vector<Triangle*> & tris, int depth) const
{	
	//�˴��ǿ�����ֵ
	KDNode* node = new KDNode(tris);
	//��Χ��
	node->aabb = tris[0]->GetAABB();
	if (tris.size() == 1)
		return node;
	for (int i = 1; i < tris.size(); ++i)
		node->aabb.Extend(tris[i]->GetAABB());
	Vector3 midPoint = Vector3(0, 0, 0);
	//������������Ϊ���ֱ�׼,С�����󣬴�������
	for (auto ptriangle : tris)
		midPoint += (ptriangle->barycentre / double(tris.size()));
	vector<Triangle*> left_tris;
	vector<Triangle*> right_tris;
	int splitAxis = node->aabb.GetLongestAxis();
	for (auto ptriangle : tris)
	{
		if (ptriangle->barycentre.GetCoord(splitAxis) < midPoint.GetCoord(splitAxis))
			left_tris.push_back(ptriangle);
		else
			right_tris.push_back(ptriangle);
	}
	if (left_tris.size() > 0)
		node->left=buildTree(left_tris, depth + 1);
	if (right_tris.size() > 0)
		node->right = buildTree(right_tris, depth + 1);
	return node;
}

void KDTree::Collide(KDNode* node,Ray& ray, Crash& crashResult)
{
	if (node->aabb.Hit(ray))
	{
		//����Ҷ�ڵ�
		if (node->left == nullptr&&node->right == nullptr)
		{
			Crash curCrash = node->triangles[0]->Collide(ray);
			if (curCrash.crashed)
				crashResult = curCrash;
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
void KDTree::Build(vector<Triangle*>& triangles)
{
	makeEmpty(root);
	root = buildTree(triangles, 0);
}
KDTree::~KDTree()
{
	makeEmpty(root);
}