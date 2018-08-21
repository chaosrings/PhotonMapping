#pragma once
#include"vector3.h"
#include"color.h"
#include"primitive.h"
#include "common.h"
#include "KDTree.h"
#include <vector>
#include <memory>
#include<sstream>
#include<string>
#include<cmath>
using std::vector;
using std::shared_ptr;

class Light {
protected:
	Color color;
	
public:
	double crashDist;
	Light(Color _color = Color(25.f,25.f, 25.f)) :color(_color){};
	~Light() {}
	Color GetColor() { return color/std::max(color.r,std::max(color.g,color.b)); }
	Color DirectIllumination(Collide collide,Vector3 toLight);
	virtual Color GetIrradiance(Collide collide, const shared_ptr<KDTree> scenekdtree)=0;
	virtual Vector3 GetCenter() = 0;
	virtual bool Intersect(Ray shadowRay) = 0;
	//virtual Photon EmitPhoton() = 0;
};

class AreaLight : public Light {
	Vector3 center, dx, dy;
public:
	AreaLight(Vector3 _center=Vector3(3.f,3.f,3.f),
		Vector3 _dx=Vector3(1.5f,0,0),
		Vector3 _dy=Vector3(0.f,1.5f,0.f))
		: Light(),center(_center),dx(_dx),dy(_dy) {}
	~AreaLight() {}
	void SetCenter(Vector3 _center) { center = _center; }
	void SetDx(Vector3 _dx) { dx = _dx; }
	void SetDy(Vector3 _dy) { dy = _dy; }
	void SetColor(Color _color) { color = _color; }
	void SetColor(Vector3 _colorVec) { color = Color(_colorVec.x, _colorVec.y, _colorVec.z); }
	Vector3 GetCenter() { return center; }
	bool Intersect(Ray shadowRay);
	Color GetIrradiance(Collide collide, const shared_ptr<KDTree> scenekdtree);
	//Photon EmitPhoton();
};
