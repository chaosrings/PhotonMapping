#include "triangle.h"
AABB Triangle::GetAABB() const
{
	AABB aabb;
	for (int i = 0; i < 3; ++i)
	{
		aabb.minCoord.GetCoord(i) = std::min(std::min(vertex[0].GetCoord(i), vertex[1].GetCoord(i)), vertex[2].GetCoord(i));
		aabb.maxCoord.GetCoord(i)= std::max(std::max(vertex[0].GetCoord(i), vertex[1].GetCoord(i)), vertex[2].GetCoord(i));
		//�����ĳһ������������ֵ���,������΢���Ű�Χ��
		if (aabb.maxCoord.GetCoord(i) - aabb.minCoord.GetCoord(i) < EPS*0.0001)
		{
			aabb.maxCoord.GetCoord(i) += EPS*0.0001;
			aabb.minCoord.GetCoord(i) -= EPS*0.0001;
		}
	}
	return aabb;
}
Collide Triangle::Intersect(Ray ray) const
{

	Collide ans;
	Vector3 origin = ray.origin;
	Vector3 dir = ray.direction.GetUnitVector();

	Vector3 E1 = this->vertex[1] - this->vertex[0];
	Vector3 E2 = this->vertex[2] - this->vertex[0];

	Vector3 P = dir*E2;

	double det = E1.Dot(P);
	Vector3 T;
	if (det > 0)
		T = origin - this->vertex[0];
	else
	{
		T = this->vertex[0] - origin;
		det = -det;
	}

	//���det����0,���뽻
	if (det < EPS)
		return ans;
	//u>0 v>0 0<u+v<1
	double u = T.Dot(P);
	if (u<0.f || u>det)
		return ans;
	
	Vector3 Q = T*E1;

	double v = dir.Dot(Q);
	if (v<0.f || u + v>det)
		return ans;

	double t = E2.Dot(Q);
	//t<0 ���ߵĸ������ཻ
	if (t < EPS)
		return ans;
	double fInvDet = 1.0f / det;
	t *= fInvDet;
	u *= fInvDet;
	v *= fInvDet;

	Vector3 texutureCoord = vertexTexutures[0] * (1 - u - v) + vertexTexutures[1] * u + vertexTexutures[2] * v;
	Vector3 normal = vertexNormals[0] * (1 - u - v) + vertexNormals[1] * u + vertexNormals[2] * v;
	normal = normal.GetUnitVector();
	
	ans.crashed = true;
	//������ײ
	ans.front = dir.Dot(this->normal) < 0;
	ans.position = vertex[0]*(1 - u - v) + vertex[1]*u + vertex[2]*v;
	//��������
	ans.u = texutureCoord.x;
	ans.v = texutureCoord.y;
	//��ײ��ķ�����
	ans.normal = ans.front ? normal : -normal;
	//���ߵ���ײ��ľ���
	ans.dist = t;
	return ans;
}	
