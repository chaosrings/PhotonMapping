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
	float minDist =float(INT_MAX);
	shared_ptr<Primitive> nearestObject=nullptr;
	for (auto object : objects)
	{
		crash = object->Collide(origin, direction);
		if (crash.crashed&& crash.dist<=minDist)
		{
			minDist = crash.dist;
			nearestObject = object;
		}
	}
	return nearestObject;
}

Crash Scene::GetFirstCrash(Vector3 origin, Vector3 direction)
{
	Crash crash;
	float minDist =float(INT_MAX);
	for (auto object : objects)
	{
		Crash temp = object->Collide(origin, direction);
		if (temp.crashed == true && temp.dist < minDist)
		{
			minDist = crash.dist;
			crash = temp;
		}
	}
	return crash;
}

shared_ptr<Light> Scene::FindNearestLight(Vector3 origin, Vector3 direction)
{
	shared_ptr<Light> nearestLight = nullptr;
	float minDist =float(INT_MAX);
	for (auto light : lights)
	{
		if (light->Collide(origin, direction)&&light->crashDist<minDist)
			nearestLight = light;
	}
	return nearestLight;
}