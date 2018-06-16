#include "raytracer.h"

Color RayTracer::RayTracing(Ray ray, int depth)
{
	Color ret;
	Crash objCrash;
	if (depth > maxRayTracingDepth)
		return Color();
	auto object = scene->FindNearestObject(ray.origin, ray.direction);
	if (object != nullptr)
		objCrash = object->Collide(ray.origin, ray.direction);
	auto  light = scene->FindNearestLight(ray.origin, ray.direction);
	if (light != nullptr&& (object==nullptr||light->crashDist<objCrash.dist))
		return light->GetColor();
	if (object != nullptr)
		return Shade(object, objCrash, ray, depth);
	return ret;
}

Color RayTracer::Shade(const shared_ptr<Primitive> object, Crash crash, Ray ray, int depth)
{
	Color ret;
	Color material = object->GetMaterial().color;
	if (object->GetMaterial().texture != nullptr)
		material =material*object->GetTexture(crash.normal);
	float diff = object->GetMaterial().diff, refl = object->GetMaterial().refl, refr = object->GetMaterial().refr;
	if (diff > EPS)
		ret += Diffusion(object, crash, ray, depth)*material*diff;
	if (refl > EPS)
		ret += Reflection(object, crash, ray, depth)*material*refl;
	if (refr > EPS)
		ret += Refraction(object, crash, ray, depth)*material*refr;
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
	float n = object->GetMaterial().rindex;
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
	SetScene(_scene);
	int H = scene->GetImageH();
	int W = scene->GetImageW();
	Bmp* result = new Bmp();
	result->Initialize(H, W);
	Vector3 eyePosition = scene->camera->GetEyePosition();
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
	}
	);
	scene->camera->Output(result);
	result->Output("result.bmp");
	delete result;
}