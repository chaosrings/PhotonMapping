#include "triangle.h"


AABB Triangle::GetAABB()
{
	AABB aabb;
	for (int i = 0; i < 3; ++i)
	{
		aabb.minCoord.GetCoord(i) = std::min(std::min(vertex0.GetCoord(i), vertex1.GetCoord(i)), vertex2.GetCoord(i));
		aabb.maxCoord.GetCoord(i)= std::max(std::max(vertex0.GetCoord(i), vertex1.GetCoord(i)), vertex2.GetCoord(i));
	}
	return aabb;
}

Crash Triangle::Collide(Ray ray)
{

	Crash ans;
	Vector3 origin = ray.origin;
	Vector3 dir = ray.direction.GetUnitVector();

	Vector3 E1 = this->vertex1 - this->vertex0;
	Vector3 E2 = this->vertex2 - this->vertex0;

	Vector3 P = dir*E2;

	double det = E1.Dot(P);
	Vector3 T;
	if (det > 0)
		T = origin - this->vertex0;
	else
	{
		T = this->vertex0 - origin;
		det = -det;
	}

	//如果det近乎0,不想交
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
	//t<0 射线的负方向不相交
	if (t < EPS)
		return ans;
	double fInvDet = 1.0f / det;
	t *= fInvDet;
	u *= fInvDet;
	v *= fInvDet;

	Vector3 normal = vertexNormals[0] * (1 - u - v) + vertexNormals[1] * u + vertexNormals[2] * v;
	normal = normal.GetUnitVector();
	ans.crashed = true;
	ans.front = dir.Dot(this->normal) < 0;
	ans.position = vertex0*(1 - u - v) + vertex1*u + vertex2*v;
	ans.normal = ans.front ? normal : -normal;
	ans.dist = ans.position.Distance(origin);
	return ans;
}	
