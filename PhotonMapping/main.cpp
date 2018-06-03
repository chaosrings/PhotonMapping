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

	/*Sphere* s = new Sphere(Vector3(0, 0, 0), 2);
	s->GetMaterial().refr = 1.0f;
	s->GetMaterial().rindex = 1.7f;
	float n = 1.7;
	Ray incident = Ray(Vector3(-1, 2, 0), Vector3(0, -1, 0));
	Crash crash = s->Collide(incident.origin, incident.direction);
	if (crash.front)
		n = 1.f / n;
	Ray afterRefr = Ray(crash.position, incident.direction.Refract(crash.normal,n));
	n = 1.7;
	crash = s->Collide(afterRefr.origin, afterRefr.direction);
	if (crash.front)
		n = 1 / n;
	
	afterRefr = Ray(crash.position, incident.direction.Refract(crash.normal, n));*/
	system("pause");
	return 0;
}