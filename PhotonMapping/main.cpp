#pragma once
#include "raytracer.h"
#include "Parser.h"
#include <random>
#include <iostream>
#include <time.h>
#include <regex>
#include <fstream>
int main()
{
	e.seed(time(nullptr));


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

	
	RayTracer* raytracer = new RayTracer();
	raytracer->Run(mainScene.get());

	delete raytracer;

	system("pause");
	return 0;
}