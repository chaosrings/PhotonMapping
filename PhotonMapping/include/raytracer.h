#pragma once
#include "common.h"
#include "color.h"
#include "scene.h"
#include "vector3.h"
#include "ray.h"
#include <ppl.h>
#include <algorithm>
class RayTracer
{
private:
	Scene* scene;
public:
	RayTracer() {}
	~RayTracer() {}
	void SetScene(Scene* _scene) { scene = _scene; }
	void Run(Scene* _scene);
	Color RayTracing(Ray ray,int depth);
	Color Shade(Collide collide, Ray ray, int depth);
	Color Reflection(Collide collide, Ray ray, int depth);
	Color Refraction(Collide collide, Ray ray, int depth);
	Color Diffusion(Collide collide, Ray ray, int depth);
};