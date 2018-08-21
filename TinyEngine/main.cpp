#pragma once
#include "raytracer.h"
#include "parser.h"
#include <random>
#include <iostream>
#include <time.h>
#include <regex>
#include <fstream>
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
	mainScene->BuildKDTree();
	RayTracer* raytracer = new RayTracer();
	raytracer->Run(mainScene.get());
	ifs.close();
	delete raytracer;
	system("pause");
	return 0;
}