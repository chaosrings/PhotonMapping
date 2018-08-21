#include "light.h"
Color Light::DirectIllumination(Collide collide,Vector3 toLight) //计算直接光照
{
	Color ret;
	double dist2 = toLight.Module2();
	toLight = toLight.GetUnitVector();
	double dot = toLight.Dot(collide.normal);
	if (dot > EPS)
	{
		double factor = dot/dist2;
		ret += color*factor;
	}
	return ret;
}
bool AreaLight::Intersect(Ray shadowRay) {
	auto origin = shadowRay.origin;
	auto direction =shadowRay.direction.GetUnitVector();
	Vector3 N = (dx * dy).GetUnitVector();
	double d = N.Dot(direction);
	if (fabs(d) < EPS) return false;
	double l = (N * center.Dot(N) - origin).Dot(N) / d;
	if (l < EPS) return false;

	Vector3 C = (origin + direction * l) - center;
	if (fabs(dx.Dot(C)) > dx.Dot(dx)) return false;
	if (fabs(dy.Dot(C)) > dy.Dot(dy)) return false;

	crashDist = l;
	return true;
}

/*
Photon AreaLight::EmitPhoton() {
	Photon ret;
	ret.power = this->color/this->color.Power();
	ret.pos = center + dx * (RandomRealZeroOne() * 2 - 1) + dy * (RandomRealZeroOne() * 2 - 1);
	ret.dir.AssRandomVector();
	return ret;
}*/
Color AreaLight::GetIrradiance(Collide collide,const shared_ptr<KDTree> scenekdtree)
{
	Color ret;
	for (int i = -2; i < 2; i++)
	{
		for (int j = -2; j < 2; j++)
		{
			//面积光源，随机测试16组阴影光线
			Vector3 toLight = center - collide.position + dx * ((RandomRealZeroOne() + i) / 2) + dy * ((RandomRealZeroOne() + j) / 2);
			double d = toLight.Module();
			Collide obscureCollide;
			scenekdtree->Intersect(Ray(collide.position, toLight.GetUnitVector()), obscureCollide);
			//如果碰撞位置与光源间没有遮挡，计算直接光照
			if (!obscureCollide.crashed||d < obscureCollide.dist)
				ret += DirectIllumination(collide,toLight);
		}
	}
	ret = ret / 16;

	return ret;
}
