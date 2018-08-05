#pragma once
#include "primitive.h"
#include "vector3.h"
#include "aabb.h"
#include "ray.h"
class Triangle : public Primitive
{
public:
	Vector3 vertex[3];   //�������������
	Vector3 vertexTexutures[3];  //����������������꣬��ʵ��vector2��������
	Vector3 vertexNormals[3];  //��������ķ�����
	Vector3 normal;
	Vector3 barycentre;
	Primitive* parent;  //���ڵ㣬ͨ��Ϊpolyhedron
	Triangle(Vector3 v0 = Vector3(), Vector3 v1 = Vector3(), Vector3 v2= Vector3()) :Primitive()
	{
		vertex[0] = v0;vertex[1]=v1;vertex[2]=v2; parent = nullptr;
	}
	AABB GetAABB() const;
	Collide Intersect(Ray ray) const;
	Vector3 GetBarycentre() const { return barycentre; }
	Primitive* GetParent() { return parent; }
};