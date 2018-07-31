#pragma once
#include <iostream>
#include "aabb.h"
using namespace std;
void testAABB()
{
	AABB aabb;
	aabb.minCoord = Vector3(0, 0, 0);
	aabb.maxCoord = Vector3(1, 1, 1);
	Ray testray;
	testray.origin = Vector3(2.f,0,2.f);
	testray.direction = Vector3(-1.f, 0, -1.f).GetUnitVector();
	if (aabb.hit(testray))
		cout << "�ཻ" << endl;
	else
		cout << "���뽻" << endl;
}