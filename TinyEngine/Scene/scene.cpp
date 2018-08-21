#include "scene.h"

Scene::Scene()
{
	
}
Scene::~Scene()
{
	objects.clear();
	lights.clear();
}

void Scene::FindNearestPrimitive(Ray ray,Collide& result)
{
	kdtree->Intersect(ray, result);
}

shared_ptr<Light> Scene::FindNearestLight(Ray shadowRay)
{
	shared_ptr<Light> nearestLight = nullptr;
	double minDist =double(INT_MAX);
	for (auto light : lights)
	{
		if (light->Intersect(shadowRay)&&light->crashDist<minDist)
			nearestLight = light;
	}
	return nearestLight;
}

void Scene::BuildKDTree()
{
	vector<Primitive*> rawPointerVec;
	for (auto autop : objects)
		rawPointerVec.push_back(autop.get());
	kdtree.reset(new KDTree());
	kdtree->BuildTree(&rawPointerVec);
}