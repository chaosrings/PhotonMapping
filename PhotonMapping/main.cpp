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
	//加一个测试三角形
	{
		shared_ptr<Triangle> testTriangle(new Triangle(Vector3(-10.f, -10.f, -3.f), Vector3(10.f, 10.f, -3.f), Vector3(-10.f, 10.f, -3.f)));
		testTriangle->normal = Vector3(0, 0, 1);
		testTriangle->GetMaterial().refl = 0.0f;
		testTriangle->GetMaterial().refr = 0.f;
		testTriangle->GetMaterial().diff = 1.f;
		testTriangle->GetMaterial().color = Color(1.f, 1.f, 1.f);
		testTriangle->vertexNormals[0]= testTriangle->vertexNormals[1]= testTriangle->vertexNormals[2]=Vector3(0, 0, 1);
		mainScene->AddObject(testTriangle);
	}
	{
		shared_ptr<Polyhedron> tp(new Polyhedron("Objects\\dragon.obj",Vector3(0,7,-1.5),3.0));
		tp->GetMaterial().refr =0.9;
		tp->GetMaterial().refl =0;
		tp->GetMaterial().diff = 0.1;
		tp->GetMaterial().color = Color(0.99,0.99,0.99);
		mainScene->AddObject(tp);
	}
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