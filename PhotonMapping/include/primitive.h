#pragma once
#include"color.h"
#include"vector3.h"
#include "bmp.h"
#include "ray.h"
#include <memory>
class Material {
public:
	Color color, absor;
	double refl, refr;
	double diff;
	double rindex;
	std::shared_ptr<Bmp>  texture;
	Material(Color _color = Color(0.5f, 0.5f, 0.5f), Color _absor = Color(0.2f, 0.2f, 0.2f),
		double _refl = 0.5f, double _refr = 0.5f, double _diff = 0.f, double _rindex = 1.6f) :
		color(_color), absor(_absor),
		refl(_refl), refr(_refr), diff(_diff), rindex(_rindex) {}
	~Material() {}

};

struct Crash
{
	bool crashed;
	Vector3 position;
	Vector3 normal;
	double dist;
	bool front;
	Crash(bool _crash = false, Vector3 _position = Vector3(), Vector3 _normal = Vector3(), double _dist = INF, bool _front = false) :
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
	virtual Crash Collide(Ray ray) = 0;  //子类必须实现Collide
	virtual Color GetTexture(Crash)  {
		return Color(1, 1, 1);
	}
};


class Plane :public Primitive
{
private:
	Vector3 normal;
	Vector3 center;
	Vector3 textureOrigin;
	double length;
	double width;
	
	Vector3 u;   //纹理width
	Vector3 v;  //纹理length

public:
	Plane(Vector3 _normal = Vector3(0, 0, 1), Vector3 _center = Vector3(0, 0, -2), double _hW = 100.f, double _hL = 100.f
	) :Primitive(), normal(_normal.GetUnitVector()), center(_center), width(_hW), length(_hL) {}

	void SetLength(double hl) {length = hl;}
	void SetWidth(double hw) { width = hw; }
	void SetCenter(Vector3 _center) { center = _center; }
	void SetNormal(Vector3 _normal) { normal = _normal; }
	Vector3 GetCenter() const { return center; }
	Vector3 GetNormal() const { return normal; }
	double GetLength() const { return length; }
	double GetWidth()const { return width; }
	void UpdateTextureOrigin();
	Crash Collide(Ray ray);
	Color GetTexture(Crash);
};