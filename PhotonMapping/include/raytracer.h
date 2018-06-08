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
	Color Shade(const shared_ptr<Primitive> object, Crash crash, Ray ray, int depth);
	Color Reflection(const shared_ptr<Primitive> object, Crash crash, Ray ray, int depth);
	Color Refraction(const shared_ptr<Primitive> object, Crash crash, Ray ray, int depth);
	Color Diffusion(const shared_ptr<Primitive> object, Crash crash, Ray ray, int depth);
};