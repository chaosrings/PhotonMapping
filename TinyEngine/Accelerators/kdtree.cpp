#include "kdtree.h"
#include <algorithm>
//包围盒
AABB KDTree::GetBoundingBox(const vector<Primitive*>& prims) const
{
	AABB res = prims[0]->GetAABB();
	for (unsigned int i = 1; i < prims.size(); ++i)
		res.Extend(prims[i]->GetAABB());
	return res;
}

//prims为物体vector的指针的原因是在堆上分配内存防止stack overflow
//若为vector<Primitive> &prims可能溢出
KDNode* KDTree::BuildTree(vector<Primitive*>* prims, int depth)
{	
	if (depth > height)
		height = depth;
	//拷贝赋值
	KDNode* node = new KDNode(*prims);
	//包围盒
	node->aabb = GetBoundingBox(*prims);
	if (prims->size() == 1)
		return node;
	Vector3 midPoint = Vector3(0, 0, 0);
	//以重心为划分标准,小于在左，大于在右
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
	//若平均重心无法分离，直接返回节点
	if (left_prims->size() == 0 || right_prims->size() == 0)
		return node;
	else
	{
		//否则继续划分
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
		//到达叶节点
		if (node->left == nullptr&&node->right == nullptr)
		{
			//对叶节点的物体遍历求交
			for (auto prim : node->primitives)
			{
				Collide curCollide = prim->Intersect(ray);
				//光线可能与多个物体，只取距离最短的
				if (curCollide.crashed&&curCollide.dist < crashResult.dist)
				{
					crashResult = curCollide;
					Triangle* triangle_prob = dynamic_cast<Triangle*>(prim);
					//如果碰撞的物体是三角形并且属于一个多面体，那么材质为polyhedron的材质
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