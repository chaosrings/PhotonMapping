#include "raytracer.h"
#include <iostream>
//#define SHOWPROGRESS
#ifdef SHOWPROGRESS
#include <Windows.h>
CRITICAL_SECTION cs;
#endif // SHOWPROGRESS
Color RayTracer::RayTracing(Ray ray, int depth)
{
	Collide collideResult;
	if (depth > maxRayTracingDepth)
		return Color();
	scene->FindNearestPrimitive(ray, collideResult);
	auto  light = scene->FindNearestLight(ray.origin, ray.direction);
	//遇到光源并且没有遮挡,直接返回光源的颜色
	if (light != nullptr && (!collideResult.crashed || light->crashDist < collideResult.dist))
		return light->GetColor();
	//否者返回物体的颜色
	if (collideResult.GetCollidePrimitive()!=nullptr)
		return Shade(collideResult,ray, depth);
	return Color();
}

Color RayTracer::Shade(Collide collide, Ray ray, int depth)
{
	Primitive* collidePrim = collide.GetCollidePrimitive();
	Color ret;
	Color material = collidePrim->GetMaterial().color;
	if (collidePrim->GetMaterial().texture.get()!=nullptr)
		material =material*(collidePrim->GetTexture(collide.u,collide.v));
	double diff = collidePrim->GetMaterial().diff, refl = collidePrim->GetMaterial().refl, refr = collidePrim->GetMaterial().refr;
	if (diff > EPS)
		ret +=material*Diffusion(collide, ray, depth)*diff;
	if (refl > EPS)
		ret +=material*Reflection(collide, ray, depth)*refl;
	if (refr > EPS)
		ret += material*Refraction(collide, ray, depth)*refr;
	return ret;
}
Color RayTracer::Reflection(Collide collide,Ray ray, int depth)
{
	Color ret;
	Ray reflRay = Ray(collide.position, ray.direction.Reflect(collide.normal));
	return  RayTracing(reflRay, depth + 1);
}
Color RayTracer::Refraction(Collide collide, Ray ray, int depth)
{
	Color ret;
	double n = collide.GetCollidePrimitive()->GetMaterial().rindex;
	if (collide.front)
		n = 1 / n;
	Ray refrRay = Ray(collide.position, ray.direction.Refract(collide.normal, n));
	return RayTracing(refrRay, depth + 1);
}

Color RayTracer::Diffusion(Collide collide, Ray ray, int depth)
{
	Color ret;
	for (auto light : scene->lights)
		ret += light->GetIrradiance(collide,scene->kdtree);
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
			Vector3 emitDirection = scene->camera->Emit(i, j).GetUnitVector();
			color += RayTracing(Ray(eyePosition, emitDirection), 0);
			scene->camera->SetColor(i, j, color.Confine());
		}
#ifdef SHOWPROGRESS
		EnterCriticalSection(&cs);
		++count;
		system("cls");
		std::cout << double(count) / double(H)<< std::endl;
		std::cout << "\r";
		LeaveCriticalSection(&cs);
#endif // SHOWPROGRESS
	}
	);
	scene->camera->Output(result);
	result->Output("result.bmp");
	delete result;
}