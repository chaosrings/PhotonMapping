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
	Color Shade(Primitive* object, Crash crash, Ray ray, int depth);
	Color Reflection(Primitive* object, Crash crash, Ray ray, int depth);
	Color Refraction(Primitive* object, Crash crash, Ray ray, int depth);
	Color Diffusion(Primitive* object, Crash crash, Ray ray, int depth);
};