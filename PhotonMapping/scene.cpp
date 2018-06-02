#include "scene.h"

Scene::Scene()
{
	
}

Scene::~Scene()
{
	for (auto pointer : objects)
		delete pointer;
	for (auto pointer : lights)
		delete pointer;
	objects.clear();
	lights.clear();
}

void Scene::Initialize()
{
	camera;//д╛хо
	Light*  areaLight = new AreaLight();//д╛хо
	lights.push_back(areaLight);
	
	
	Sphere* sphere = new Sphere();
	sphere->GetMaterial().color = Color(0.99f, 0.99f, 0.99f);
	sphere->GetMaterial().diff = 0.f;
	sphere->GetMaterial().refl = 0.f;
	sphere->GetMaterial().refr = 1.f;
	sphere->GetMaterial().rindex = 1.7f;
	sphere->center = Vector3(-0.5f, 5.14f, -1.8f);
	sphere->radius = 0.2f;
	objects.push_back(sphere);

	sphere = new Sphere();
	sphere->GetMaterial().color = Color(0.99f, 0.99f, 0.99f);
	sphere->GetMaterial().diff = 0.f;
	sphere->GetMaterial().refl = 0.5f;
	sphere->GetMaterial().refr = 0.5f;
	sphere->GetMaterial().rindex = 1.7f;
	sphere->center = Vector3(-0.5f, 4.64f, -1.8f);
	sphere->radius = 0.4f;
	objects.push_back(sphere);
	
	//bottom
	Plane* plane = new Plane();
	plane->GetMaterial().color = Color(0.75f, 0.75f, 0.75f);
	plane->GetMaterial().diff = 1.f;
	plane->GetMaterial().refl = 0.f;
	plane->GetMaterial().refr = 0.f;
	objects.push_back(plane);
}


Primitive* Scene::FindNearestObject(Vector3 origin, Vector3 direction)
{
	Crash crash;
	float minDist = INT_MAX;
	Primitive* nearestObject=nullptr;
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
	float minDist = 3e37;
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

Light* Scene::FindNearestLight(Vector3 origin, Vector3 direction)
{
	Light* nearestLight = nullptr;
	float minDist = INT_MAX;
	for (auto light : lights)
	{
		
		if (light->Collide(origin, direction)&&light->crashDist<minDist)
			nearestLight = light;
	}
	return nearestLight;
}