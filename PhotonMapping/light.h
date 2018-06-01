#pragma once
#include"vector3.h"
#include"color.h"
#include"primitive.h"
#include"photonmap.h"
#include "common.h"
#include<sstream>
#include<string>
#include<cmath>

class Light {
protected:
	Color color;
public:
	float crashDist;
	Light(Color _color = Color(1.f, 1.f, 1.f)) :color(_color) {};
	~Light() {}


	Color GetColor() { return color; }
	Color DirectIllumination(Crash crash, Vector3& toLight);
	virtual bool Collide(Vector3& origin, Vector3& direction) = 0;
	virtual Photon EmitPhoton() = 0;
};

class AreaLight : public Light {
	Vector3 center, dx, dy;
public:
	AreaLight(Vector3 _center=Vector3(50,81.33f,81.6f),
		Vector3 _dx=Vector3(5.f,0,0),
		Vector3 _dy=Vector3(0,0,-5.f))
		: Light(),dx(_dx),dy(_dy) {}
	~AreaLight() {}

	bool Collide(Vector3& origin, Vector3& direction);
	Color GetIrradiance(Crash crash, std::vector<Primitive*>& primitives );
	Photon EmitPhoton();
};
