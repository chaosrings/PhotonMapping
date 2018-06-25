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
	float t1 = normal.Dot(center - origin);
	if (t1 > EPS)   //与0比较为何不可？
		crash.front = false;
	else
		crash.front = true;
	float t2 = direction.Dot(normal);
	float t = t1 / t2;
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
	float tu = (pos - textureOrigin).Dot(u) / (width*width);
	float tv = (pos - textureOrigin).Dot(v) / (length*length);
	
	Color ret;
	if (material.texture.get()!= nullptr)
		ret = material.texture->GetSmoothColor(clamp<float>(tu, 0.f, 1.f), clamp<float>(tv, 0.f, 1.f));
	return ret;
}


Crash  Sphere::Collide(Ray ray)
{
	Crash crash;
	auto direction = ray.direction.GetUnitVector();
	auto origin = ray.origin;
	Vector3 P = origin - center;
	float b = -P.Dot(direction);
	float det = b * b - P.Module2() + radius * radius;

	if (det > EPS) {
		det = sqrt(det);
		float x1 = b - det, x2 = b + det;

		if (x2 < EPS) { crash.crashed = false; return crash; }
		crash.crashed = true;
		if (x1 > EPS) {
			crash.dist = x1;
			crash.front = true;
		}
		else {
			crash.dist = x2;
			crash.front = false;
		}
	}
	else
	{
		crash.crashed = false;
		return crash;
	}

	crash.position = origin + direction * crash.dist;
	crash.normal = (crash.position - center).GetUnitVector();
	if (crash.front == false)
		crash.normal = -crash.normal;
	return crash;
}

Color Sphere::GetTexture(Crash crash)
{
	auto normal = crash.normal;
	normal = normal.GetUnitVector();
	float u = asin(normal.x) / PI + 0.5f;
	float v = asin(normal.y) / PI + 0.5f;
	return (this->material.texture)->GetSmoothColor(u, v);
}