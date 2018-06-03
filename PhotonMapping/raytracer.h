#pragma once
#include "common.h"
#include "color.h"
#include "scene.h"

class RayTracer
{
private:
	 Scene* scene;
	PhotonMap* photonmap;
public:
	RayTracer() {}
	~RayTracer() {}
	void SetScene(Scene* _scene) { scene = _scene; }
	void SetPhotonMap(PhotonMap* _photonmap) {photonmap = _photonmap;	}
	void Run(Scene* _scene, PhotonMap* _photonmap);
	Color RayTracing(Ray ray,int depth);
	Color RayReflection(Primitive* object, Crash crash, Ray ray, int depth);
	Color RayRefraction(Primitive* object, Crash crash, Ray ray, int depth);
	Color RayDiffusion(Primitive* object, Crash crash, Ray ray, int depth);
};