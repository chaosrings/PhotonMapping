#include "raytracer.h"
#include "Vector3.h"

#include <ppl.h>
Color RayTracer::RayTracing(Ray ray, int depth)
{
	Color ret;
	Crash objCrash;
	if (depth > maxRayTracingDepth)
		return ret;
	Primitive* object = scene->FindNearestObject(ray.origin,ray.direction);
	if(object!=nullptr)
		objCrash = object->Collide(ray.origin, ray.direction);
	Light*  light = scene->FindNearestLight(ray.origin, ray.direction);

	if (light != nullptr&& (object==nullptr||light->crashDist<objCrash.dist))
	{
		ret += light->GetColor();
	}
	if (object != nullptr)
	{
		if (depth > 40)
			return object->GetMaterial().color;
		if (object->GetMaterial().refl > EPS)
			ret += RayReflection(object, objCrash,ray ,depth + 1);
		if(object->GetMaterial().refr>EPS)
			ret += RayRefraction(object, objCrash,ray,depth + 1);
		if (object->GetMaterial().diff > EPS)
			ret += RayDiffusion(object, objCrash, ray,depth + 1);

	}
	return ret;
}

Color RayTracer::RayReflection(Primitive* object, Crash crash,Ray ray, int depth)
{
	Color ret;
	Ray reflRay = Ray(crash.position, ray.direction.Reflect(crash.normal));
	ret = RayTracing(reflRay, depth + 1)*object->GetMaterial().color;
	ret *= object->GetMaterial().refl;
	return ret;
}
Color RayTracer::RayRefraction(Primitive* object, Crash crash, Ray ray, int depth)
{
	Color ret;
	float n = object->GetMaterial().rindex;
	if (crash.front)
		n = 1 / n;
	Ray refrRay = Ray(crash.position, ray.direction.Refract(crash.normal, n));
	ret = RayTracing(refrRay, depth + 1)*object->GetMaterial().color;
	ret *= object->GetMaterial().refr;
	return ret;
}

Color RayTracer::RayDiffusion(Primitive* object, Crash crash, Ray ray, int depth)
{
	Color ret;
	for (auto light : scene->lights)
		ret += light->GetIrradiance(crash, object, scene->objects)*object->GetMaterial().color;
	ret += photonmap->GetIrradiance(crash.position, crash.normal, 0.1f,100)*object->GetMaterial().color;
	/*Ray rayDiff = Ray(crash.position, crash.normal.Diffuse(crash.normal));
	ret = RayTracing(rayDiff, depth + 1);*/
	ret *= object->GetMaterial().diff;
	return ret;
}

void RayTracer::Run(Scene* _scene,PhotonMap* _photonmap)
{
	SetScene(_scene);
	SetPhotonMap(_photonmap);
	int H = scene->GetImageH();
	int W = scene->GetImageW();
	Bmp* result = new Bmp(H, W);
	Vector3 eyePosition = scene->camera.GetEyePosition();
	concurrency::parallel_for(0, H, [&](int i)
	{
		for (int j = 0; j < W; ++j)
		{
			Vector3 emitDirection = scene->camera.Emit(i, j);
			Color color = RayTracing(Ray(eyePosition, emitDirection), 0);
			color.Confine();
			scene->camera.SetColor(i, j, color);
		} 
	}
	);

	scene->camera.Output(result);
	result->Output("result.bmp");
	delete result;
}