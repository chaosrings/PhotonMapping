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
	float power;
	
public:
	float crashDist;
	Light(Color _color = Color(1.f,1.f, 1.f),float _power=25.f) :color(_color),power(_power){};
	~Light() {}
	

	Color GetColor() { return color*this->power; }
	void SetPower(float _power) { power = _power; }
	Color DirectIllumination(Crash crash, Primitive* object, Vector3 toLight);
	virtual Color GetIrradiance(Crash crash, Primitive* object, std::vector<Primitive*>& primitives)=0;
	virtual Vector3 GetCenter() = 0;
	virtual bool Collide(Vector3 origin, Vector3 direction) = 0;
	virtual Photon EmitPhoton() = 0;
};

class AreaLight : public Light {
	Vector3 center, dx, dy;
public:
	AreaLight(Vector3 _center=Vector3(3.f,3.f,3.f),
		Vector3 _dx=Vector3(3.f,0,0),
		Vector3 _dy=Vector3(0.f,3.f,0.f))
		: Light(),center(_center),dx(_dx),dy(_dy) {}
	~AreaLight() {}

	Vector3 GetCenter() { return center; }
	bool Collide(Vector3 origin, Vector3 direction);
	Color GetIrradiance(Crash crash, Primitive* object, std::vector<Primitive*>& primitives);
	Photon EmitPhoton();
};
