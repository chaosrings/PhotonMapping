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
	
	Sphere* sphere = nullptr;

	sphere = new Sphere();
	sphere->GetMaterial().color = Color(0.f, 1.f, 1.f);
	sphere->GetMaterial().diff = 0.f;
	sphere->GetMaterial().refl = 0.f;
	sphere->GetMaterial().refr = 1.f;
	sphere->GetMaterial().rindex = 1.7f;
	sphere->center = Vector3(-0.5f, 5.14f, -1.8f);
	sphere->radius = 0.2f;
	objects.push_back(sphere);

	sphere = new Sphere();
	sphere->GetMaterial().color = Color(1.f, 1.f, 0.f);
	sphere->GetMaterial().diff = 0.f;
	sphere->GetMaterial().refl = 0.f;
	sphere->GetMaterial().refr = 1.f;
	sphere->GetMaterial().rindex = 1.7f;
	sphere->center = Vector3(0.f, 5.14f, -1.8f);
	sphere->radius = 0.2f;
	objects.push_back(sphere);

	sphere = new Sphere();
	sphere->GetMaterial().color = Color(0.f, 0.f, 1.f);
	sphere->GetMaterial().diff = 0.f;
	sphere->GetMaterial().refl = 0.f;
	sphere->GetMaterial().refr = 1.f;
	sphere->GetMaterial().rindex = 1.7f;
	sphere->center = Vector3(0.5f, 5.14f, -1.8f);
	sphere->radius = 0.2f;
	objects.push_back(sphere);


	sphere = new Sphere();
	sphere->GetMaterial().color = Color(1.f, 1.f, 1.f);
	sphere->GetMaterial().diff = 0.0f;
	sphere->GetMaterial().refl = 0.2f;
	sphere->GetMaterial().refr = 0.8f;
	sphere->GetMaterial().rindex = 1.8f;
	sphere->center = Vector3(0.f,6.f, -1.5f);
	sphere->radius = 0.5f;
	objects.push_back(sphere);

	sphere = new Sphere();
	sphere->GetMaterial().color = Color(1.f,1.f, 1.f);
	sphere->GetMaterial().diff = 0.f;
	sphere->GetMaterial().refl = 1.f;
	sphere->GetMaterial().refr = 0.f;
	sphere->GetMaterial().rindex = 1.7f;
	sphere->center = Vector3(1.5f, 6.3f, -1.6f);
	sphere->radius = 0.4f;
	objects.push_back(sphere);
	

	//bottom
	Plane* plane = new Plane();
	plane->GetMaterial().color = Color(0.75f, 0.75f, 0.75f);
	plane->GetMaterial().diff = 1.f;
	plane->GetMaterial().refl = 0.f;
	plane->GetMaterial().refr = 0.f;
	objects.push_back(plane);

	//top
	plane = new Plane();
	plane->center = Vector3(3, 3, 3.01f);
	plane->normal = Vector3(0, 0, -1.f);
	plane->GetMaterial().color = Color(0.75f, 0.75f, 0.75f);
	plane->GetMaterial().diff = 1.f;
	plane->GetMaterial().refl = 0.f;
	plane->GetMaterial().refr = 0.f;
	objects.push_back(plane);



	//left
	plane = new Plane();
	plane->GetMaterial().color = Color(0.75f, 0.f, 0.f);
	plane->center = Vector3(0,10.f, 0);
	plane->normal = Vector3(0, -1.f, 0);
	plane->GetMaterial().diff = 1.f;
	plane->GetMaterial().refl = 0.f;
	plane->GetMaterial().refr = 0.f;
	objects.push_back(plane);

	//right
	plane = new Plane();
	plane->GetMaterial().color = Color(0.f, 0.f, 0.75f);
	plane->center = Vector3(0, -7.f, 0);
	plane->normal = Vector3(0, 1.f, 0);
	plane->GetMaterial().diff = 1.f;
	plane->GetMaterial().refl = 0.f;
	plane->GetMaterial().refr = 0.f;
	objects.push_back(plane);

	//back
	plane = new Plane();
	plane->GetMaterial().color = Color(0.75f, 0.75f, 0.75f);
	plane->center = Vector3(7.f, 0.f,0.f);
	plane->normal = Vector3(-1.f, 0, 0);
	plane->GetMaterial().diff = 1.f;
	plane->GetMaterial().refl = 0.f;
	plane->GetMaterial().refr = 0.f;
	objects.push_back(plane);

	//front
	plane = new Plane();
	plane->GetMaterial().color = Color(0.f, 0.f, 0.75f);
	plane->center = Vector3(-7.f, 0, 0);
	plane->normal = Vector3(1.f, 0, 0);
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