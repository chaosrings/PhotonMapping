#pragma once
#include "raytracer.h"
#include "Parser.h"
#include <random>
#include <iostream>
#include <time.h>
int main()
{
	/*e.seed(time(nullptr));

	Scene* mainScene = new Scene();
	mainScene->Initialize();

	
	RayTracer* raytracer = new RayTracer();
	raytracer->Run(mainScene);

	delete raytracer;
	delete mainScene;
*/

	string toParser = "AreaLight\ncenter=3.0 3.0 3.0\ndx=1.5 0 0\ndy=0 1.5 0\ncolor=25.0 25 25.0\n";
	Parser parser(move(toParser));
	toParser.clear();
	auto s = parser.scene();
	system("pause");
	return 0;
}