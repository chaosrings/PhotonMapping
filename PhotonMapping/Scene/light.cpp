#include "light.h"
Color Light::DirectIllumination(Crash crash,Primitive* object, Vector3 toLight) //计算直接光照
{
	Color ret;
	float dist2 = toLight.Module2();
	toLight = toLight.GetUnitVector();
	float dot = toLight.Dot(crash.normal);

	if (dot > EPS)
	{
		float factor = dot/dist2;
		ret += color*factor;
	}
	return ret;
}


bool AreaLight::Collide(Vector3 origin, Vector3 direction) {
	direction = direction.GetUnitVector();
	Vector3 N = (dx * dy).GetUnitVector();
	float d = N.Dot(direction);
	if (fabs(d) < EPS) return false;
	float l = (N * center.Dot(N) - origin).Dot(N) / d;
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

Color AreaLight::GetIrradiance(Crash crash,Primitive* object, std::vector<Primitive*>& primitives) 
{
	Color ret;
	for (int i = -2; i < 2; i++)
	{
		for (int j = -2; j < 2; j++)
		{
			Vector3 toLight = center - crash.position + dx * ((RandomRealZeroOne() + i) / 2) + dy * ((RandomRealZeroOne() + j) / 2);
			float dist = toLight.Module();
			bool shade = false;
			for (auto pri : primitives)
			{
				Crash curCrash = pri->Collide(crash.position, toLight);
				if (curCrash.crashed && curCrash.dist < dist)
				{
					shade = true;
					break;
				}
			}
			if (shade == false)
				ret += DirectIllumination(crash, object, toLight);
		}
	}
	ret = ret / 16;

	return ret;
}
