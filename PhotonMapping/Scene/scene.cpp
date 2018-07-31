#include "scene.h"

Scene::Scene()
{
	
}

Scene::~Scene()
{
	objects.clear();
	lights.clear();
}


shared_ptr<Primitive> Scene::FindNearestObject(Vector3 origin, Vector3 direction)
{
	Crash crash;
	double minDist =double(INT_MAX);
	shared_ptr<Primitive> nearestObject=nullptr;
	for (auto object : objects)
	{
		crash = object->Collide(Ray(origin,direction));
		if (crash.crashed&& crash.dist<=minDist)
		{
			minDist = crash.dist;
			nearestObject = object;
		}
	}
	return nearestObject;
}


shared_ptr<Light> Scene::FindNearestLight(Vector3 origin, Vector3 direction)
{
	shared_ptr<Light> nearestLight = nullptr;
	double minDist =double(INT_MAX);
	for (auto light : lights)
	{
		if (light->Collide(origin, direction)&&light->crashDist<minDist)
			nearestLight = light;
	}
	return nearestLight;
}