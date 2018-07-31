#include "raytracer.h"
#include <iostream>
#define SHOWPROGRESS
#ifdef SHOWPROGRESS
#include <Windows.h>

CRITICAL_SECTION cs;
#endif // SHOWPROGRESS


Color RayTracer::RayTracing(Ray ray, int depth)
{
	Crash objCrash;
	if (depth > maxRayTracingDepth)
		return Color();
	auto object = scene->FindNearestObject(ray.origin, ray.direction);
	if (object != nullptr)
		objCrash = object->Collide(ray);
	auto  light = scene->FindNearestLight(ray.origin, ray.direction);
	if (light != nullptr&& (object==nullptr||light->crashDist<objCrash.dist))
		return light->GetColor();
	if (object != nullptr)
		return Shade(object, objCrash, ray, depth);
	return Color();
}

Color RayTracer::Shade(const shared_ptr<Primitive> object, Crash crash, Ray ray, int depth)
{
	Color ret;
	Color material = object->GetMaterial().color;
	if (object->GetMaterial().texture.get()!=nullptr)
		material =material*(object->GetTexture(crash));
	double diff = object->GetMaterial().diff, refl = object->GetMaterial().refl, refr = object->GetMaterial().refr;
	if (diff > EPS)
		ret +=material*Diffusion(object, crash, ray, depth)*diff;
	if (refl > EPS)
		ret +=material*Reflection(object, crash, ray, depth)*refl;
	if (refr > EPS)
		ret += material*Refraction(object, crash, ray, depth)*refr;
	return ret;
}


Color RayTracer::Reflection(const shared_ptr<Primitive> object, Crash crash,Ray ray, int depth)
{
	Color ret;
	Ray reflRay = Ray(crash.position, ray.direction.Reflect(crash.normal));
	return  RayTracing(reflRay, depth + 1);
}
Color RayTracer::Refraction(const shared_ptr<Primitive> object, Crash crash, Ray ray, int depth)
{
	Color ret;
	double n = object->GetMaterial().rindex;
	if (crash.front)
		n = 1 / n;
	Ray refrRay = Ray(crash.position, ray.direction.Refract(crash.normal, n));
	return RayTracing(refrRay, depth + 1);
}

Color RayTracer::Diffusion(const shared_ptr<Primitive> object, Crash crash, Ray ray, int depth)
{
	Color ret;
	for (auto light : scene->lights)
		ret += light->GetIrradiance(crash, object, scene->objects);
	return ret;
}

void RayTracer::Run(Scene* _scene)
{
#ifdef SHOWPROGRESS
	InitializeCriticalSection(&cs);
#endif // SHOWPROGRESS

	SetScene(_scene);
	int H = scene->GetImageH();
	int W = scene->GetImageW();
	Bmp* result = new Bmp();
	result->Initialize(H, W);
	Vector3 eyePosition = scene->camera->GetEyePosition();
	int count = 0;
	concurrency::parallel_for(0, H, [&](int i)
	{
		for (int j = 0; j < W; ++j)
		{
			Color color;
			Vector3 emitDirection = scene->camera->Emit(i, j);
			color += RayTracing(Ray(eyePosition, emitDirection), 0);
			color.Confine();
			scene->camera->SetColor(i, j, color);
		}
#ifdef SHOWPROGRESS
		EnterCriticalSection(&cs);
#endif // SHOWPROGRESS
		++count;
		std::cout << double(count) / double(H)<< std::endl;
		std::cout << "\r";
#ifdef SHOWPROGRESS
		LeaveCriticalSection(&cs);
#endif // SHOWPROGRESS
	}


	);
	scene->camera->Output(result);
	result->Output("result.bmp");
	delete result;
}