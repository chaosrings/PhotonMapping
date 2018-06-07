#pragma once
#include "raytracer.h"
#include <random>
#include <iostream>
#include <time.h>
int main()
{
	e.seed(time(nullptr));

	Scene* mainScene = new Scene();
	mainScene->Initialize();

	
	RayTracer* raytracer = new RayTracer();
	raytracer->Run(mainScene);

	delete raytracer;
	delete mainScene;

	system("pause");
	return 0;
}