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
		testTriangle->GetMaterial().refl = 0.0f;
		testTriangle->GetMaterial().refr = 0.f;
		testTriangle->GetMaterial().diff = 1.f;
		testTriangle->GetMaterial().color = Color(1.f, 1.f, 1.f);
		mainScene->AddObject(testTriangle);
	}
	//暴力加三角形
	/*{
		SimpleObjReader reader;
		vector<Triangle> ans = reader.ReadObjFile("Objects\\bunny.obj");
		Vector3 offset(0.0, 7.5,-1.5);
		for (auto tri : ans)
		{
			shared_ptr<Triangle> tri_ptr(new Triangle(tri.vertex0 + offset, tri.vertex1 + offset, tri.vertex2 + offset));
			tri_ptr->GetMaterial().refl = 0.5;
			tri_ptr->GetMaterial().refr = 0.5;
			tri_ptr->GetMaterial().diff = 0.0;
			tri_ptr->GetMaterial().color = Color(1.f, 1.f, 1.f);
			mainScene->AddObject(tri_ptr);
		}
	}*/
	{
		shared_ptr<Polyhedron> tp(new Polyhedron("Objects\\bunny2.obj",Vector3(0,7.5,-1.5),3.0));
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