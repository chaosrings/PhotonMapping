#include "kdtree.h"
#include <algorithm>
//��Χ��
AABB KDTree::GetBoundingBox(const vector<Primitive*>& prims) const
{
	AABB res = prims[0]->GetAABB();
	for (unsigned int i = 1; i < prims.size(); ++i)
		res.Extend(prims[i]->GetAABB());
	return res;
}

//primsΪ����vector��ָ���ԭ�����ڶ��Ϸ����ڴ��ֹstack overflow
//��Ϊvector<Primitive> &prims�������
KDNode* KDTree::BuildTree(vector<Primitive*>* prims, int depth)
{	
	if (depth > height)
		height = depth;
	//������ֵ
	KDNode* node = new KDNode(*prims);
	//��Χ��
	node->aabb = GetBoundingBox(*prims);
	if (prims->size() == 1)
		return node;
	Vector3 midPoint = Vector3(0, 0, 0);
	//������Ϊ���ֱ�׼,С�����󣬴�������
	for (auto prim : *prims)
		midPoint += (prim->GetBarycentre()/ double(prims->size()));
	auto left_prims=new vector<Primitive*>();
	auto right_prims= new vector<Primitive*>();
	int splitAxis = node->aabb.GetLongestAxis();
	for (auto prim :*prims)
	{
		if (prim->GetBarycentre().GetCoord(splitAxis) < midPoint.GetCoord(splitAxis))
			left_prims->push_back(prim);
		else
			right_prims->push_back(prim);
	}
	//��ƽ�������޷����룬ֱ�ӷ��ؽڵ�
	if (left_prims->size() == 0 || right_prims->size() == 0)
		return node;
	else
	{
		//�����������
		node->left = BuildTree(left_prims, depth + 1);
		node->right = BuildTree(right_prims, depth + 1);
	}
	delete left_prims;
	delete right_prims;
	return node;
}
void KDTree::BuildTree(vector<Primitive*>* prims)
{
	makeEmpty(root);
	root = BuildTree(prims, 0);
}
void KDTree::Intersect(KDNode* node,Ray& ray, Collide& crashResult) const
{
	if (node->aabb.Hit(ray))
	{
		//����Ҷ�ڵ�
		if (node->left == nullptr&&node->right == nullptr)
		{
			//��Ҷ�ڵ�����������
			for (auto prim : node->primitives)
			{
				Collide curCollide = prim->Intersect(ray);
				//���߿����������壬ֻȡ������̵�
				if (curCollide.crashed&&curCollide.dist < crashResult.dist)
				{
					crashResult = curCollide;
					Triangle* triangle_prob = dynamic_cast<Triangle*>(prim);
					//�����ײ�������������β�������һ�������壬��ô����Ϊpolyhedron�Ĳ���
					if (triangle_prob != nullptr&&triangle_prob->GetParent()!=nullptr)
						crashResult.SetCollidePrimitive(triangle_prob->GetParent());
					else
						crashResult.SetCollidePrimitive(prim);
				}
			}
		}
		else
		{
			if (node->left != nullptr)
				Intersect(node->left, ray, crashResult);
			if (node->right != nullptr)
				Intersect(node->right, ray, crashResult);
		}
	}
}
void KDTree::Intersect(Ray& ray, Collide& crashResult) const
{
	Intersect(root, ray, crashResult);
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
KDTree::~KDTree()
{
	makeEmpty(root);
}