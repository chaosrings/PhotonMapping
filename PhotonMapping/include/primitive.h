#pragma once
#include"color.h"
#include"vector3.h"
#include "bmp.h"
#include <memory>
class Material {
public:
	Color color, absor;
	float refl, refr;
	float diff;
	float rindex;
	std::shared_ptr<Bmp>  texture;
	Material(Color _color = Color(0.5f, 0.5f, 0.5f), Color _absor = Color(0.2f, 0.2f, 0.2f),
		float _refl = 0.5f, float _refr = 0.5f, float _diff = 0.f, float _rindex = 1.6f) :
		color(_color), absor(_absor),
		refl(_refl), refr(_refr), diff(_diff), rindex(_rindex) {}
	~Material() {}

};

struct Crash
{
	bool crashed;
	Vector3 position;
	Vector3 normal;
	float dist;
	bool front;
	Crash(bool _crash = false, Vector3 _position = Vector3(), Vector3 _normal = Vector3(), float _dist = 0, bool _front = false) :
		crashed(_crash), position(_position), normal(_normal), dist(_dist), front(_front) {
	}
};

class Primitive
{
protected:
	Material material;
public:
	Primitive() {};
	virtual ~Primitive() {};
	void SetMaterial(Material mat) { material = mat; }
	Material& GetMaterial() { return material; }
	virtual Crash Collide(Vector3 origin, Vector3 direction) = 0;  //子类必须实现Collide
	virtual Color GetTexture(Vector3)  {
		return Color(1, 1, 1);
	}
};

class Sphere : public Primitive
{
private:
	Vector3 center;
	float radius;
public:
	Sphere(Vector3 _center = Vector3(), float _radius = 0.f) :Primitive(), center(_center), radius(_radius) {};
	~Sphere() {}
	
	void SetCenter(Vector3 _center) { center = _center; }
	void SetRadius(float r) { radius = r; }
	
	Vector3 GetCenter() const  { return center; }
	Vector3 GetRadius() const  { return radius; }
	Color GetTexture(Vector3 normal) ;
	Crash Collide(Vector3 origin, Vector3 direction);
};

class Plane :public Primitive
{
private:
	Vector3 normal;
	Vector3 center;
	float  halfLength;
	float  halfWidth;
public:
	Plane(Vector3 _normal = Vector3(0, 0, 1), Vector3 _center = Vector3(0, 0, -2), float _hW = 100.f, float _hL = 100.f
	) :Primitive(), normal(_normal.GetUnitVector()), center(_center), halfWidth(_hW), halfLength(_hL) {}

	void SetHL(float hl) {halfLength = hl;}
	void SetHW(float hw) { halfWidth = hw; }
	Vector3 GetCenter() const { return center; }
	Vector3 GetNormal() const { return normal; }
	float GetHalfLength() const { return halfLength; }
	float GetHalfWidth()const { return halfWidth; }
	Crash Collide(Vector3 origin, Vector3 direction);
	Color GetTexture(Vector3 pos);
};