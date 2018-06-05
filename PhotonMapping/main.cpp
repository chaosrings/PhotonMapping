#pragma once
#include "photontracer.h"
#include "raytracer.h"
#include <random>
#include <iostream>
#include <time.h>
int main()
{
	e.seed(time(nullptr));

	Scene* mainScene = new Scene();
	mainScene->Initialize();
	PhotonTracer* photontracer = new PhotonTracer();
	photontracer->Run(mainScene);
	
	RayTracer* raytracer = new RayTracer();
	raytracer->Run(mainScene, photontracer->GetPhotonMap());

	delete photontracer;
	delete raytracer;
	delete mainScene;

	system("pause");
	return 0;
}