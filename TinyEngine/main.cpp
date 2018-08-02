#pragma once
#include "raytracer.h"
#include "parser.h"
#include <random>
#include <iostream>
#include <time.h>
#include <regex>
#include <fstream>

void RunRayTracer()
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
	//µÿ√Ê
	{
		shared_ptr<Triangle> testTriangle(new Triangle(Vector3(-10.f, -10.f, -2.f), Vector3(10.f, 10.f, -2.f), Vector3(-10.f, 10.f, -2.f)));
		testTriangle->normal = Vector3(0, 0, 1);
		testTriangle->GetMaterial().refl = 0.5;
		testTriangle->GetMaterial().refr = 0;
		testTriangle->GetMaterial().diff = 0.5;
		testTriangle->GetMaterial().color = Color(1,1,1);
		testTriangle->vertexNormals[0]= testTriangle->vertexNormals[1]= testTriangle->vertexNormals[2]=Vector3(0, 0, 1);
		mainScene->AddObject(testTriangle);
	}
	mainScene->BuildKDTree();
	RayTracer* raytracer = new RayTracer();
	raytracer->Run(mainScene.get());
	delete raytracer;
}

int main()
{
	RunRayTracer();
	system("pause");
	return 0;
}