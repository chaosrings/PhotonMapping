#include "light.h"


Color Light::DirectIllumination(Crash crash, Vector3& toLight) //计算直接光照
{
	Color ret;
	float dist2 = toLight.Module2();
	toLight = toLight.GetUnitVector();
	float dot = toLight.Dot(crash.normal);

	if (dot > EPS)     //光的功率*cos(theta)/距离的平方
		ret += color*dot / dist2;
	return ret;
}


bool AreaLight::Collide(Vector3& origin, Vector3& direction) {
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


Photon AreaLight::EmitPhoton() {
	Photon ret;
	ret.power = color / color.Power();
	ret.pos = center + dx * (u(e) * 2 - 1) + dy * (u(e) * 2 - 1);
	ret.dir = ret.dir.Diffuse(dx*dy);
	return ret;
}

Color AreaLight::GetIrradiance(Crash crash, std::vector<Primitive*>& primitives) {
	Color ret;
	for (int i = 0; i < 2; i++)
		for (int j =0; j < 2; j++)
		{
				Vector3 toLight = center - crash.position + dx * ((u(e) + i) / 2) + dy * ((u(e) + j) / 2);
				float dist = toLight.Module();
				bool shade = false;
				for (auto pri : primitives)
				{
					Crash curCrash = pri->Collide(crash.position, toLight);
					if (curCrash.crashed && curCrash.dist<dist)
					{
						shade = true;
						break;
					}
				}
				if (shade == false) 
					ret += DirectIllumination(crash, toLight);
			}
	ret /= 4.f;

	return ret;
}
