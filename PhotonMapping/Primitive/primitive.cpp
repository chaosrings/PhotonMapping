#include "primitive.h"
void Plane::UpdateTextureOrigin()
{
	u = normal.GetAnVerticalVector();
	v = normal*u;
	this->textureOrigin = center - u*(length/2) - v*(width/2);
	u = u*width;
	v = v*length;
}
Crash Plane::Collide(Ray ray)
{
	Crash crash;
	
	auto direction = ray.direction.GetUnitVector();
	auto origin = ray.origin;
	normal = normal.GetUnitVector();
	double t1 = normal.Dot(center - origin);
	if (t1 > EPS)   //与0比较为何不可？
		crash.front = false;
	else
		crash.front = true;
	double t2 = direction.Dot(normal);
	double t = t1 / t2;
	if (t <EPS)	//与0比较为何不可？
	{
		crash.crashed = false;
		return crash;
	}
	crash.position = origin + direction*t;
	crash.dist = t;
	if ((crash.position - textureOrigin).Dot(u) > width*width || (crash.position - textureOrigin).Dot(v)>length*length)
	{
		crash.crashed = false;
		return crash;
	}
	crash.crashed = true;
	crash.normal = (crash.front) ? normal : -normal;
	return crash;
}

Color Plane::GetTexture(Crash crash)
{
	auto pos = crash.position;
	double tu = (pos - textureOrigin).Dot(u) / (width*width);
	double tv = (pos - textureOrigin).Dot(v) / (length*length);
	Color ret;
	if (material.texture.get()!= nullptr)
		ret = material.texture->GetSmoothColor(clamp<double>(tu, 0.f, 1.f), clamp<double>(tv, 0.f, 1.f));
	return ret;
}


