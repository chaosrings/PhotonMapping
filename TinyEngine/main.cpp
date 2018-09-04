#pragma once
#include "raytracer.h"
#include "parser.h"
#include <random>
#include <iostream>
#include <time.h>
#include <regex>
#include <fstream>
#define  AddRamdomRefrSphere
int main()
{
	e.seed(static_cast<unsigned int>(time(nullptr)));
	ifstream ifs("scene.txt");
	string toParser = "";
	string line;

	while (getline(ifs, line))
	{
		line += '\n';
		toParser += line;
	}
	Parser parser(move(toParser));
	shared_ptr<Scene> mainScene = parser.scene();
#ifdef AddRamdomRefrSphere
	for (int i = 0; i < 10; ++i)
	{
		Vector3 position = Vector3(1.5 + (-5)+RandomRealZeroOne() * 10, 5.5 + (-5)+RandomRealZeroOne() * 10, RandomRealZeroOne() * 10);
		shared_ptr<Sphere> newSphere(new Sphere(position, RandomRealZeroOne()));
		newSphere->GetMaterial().color = Color(1, 1, 1);
		newSphere->GetMaterial().refr = 1;
		newSphere->GetMaterial().refl = 0;
		newSphere->GetMaterial().diff = 0;
		mainScene->AddObject(newSphere);
	}
#endif // AddRamdomRefrSphere

	mainScene->BuildKDTree();
	RayTracer* raytracer = new RayTracer();
	raytracer->Run(mainScene.get());
	ifs.close();
	delete raytracer;
	system("pause");
	return 0;
}