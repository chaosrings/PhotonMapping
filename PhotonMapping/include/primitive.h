#pragma once
#include"color.h"
#include"vector3.h"
#include "bmp.h"
#include "ray.h"
#include "aabb.h"
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
	//必须实现光线碰撞检测
	virtual Crash Collide(Ray ray) const = 0;  
	//必须实现包围盒
	virtual AABB  GetAABB() const = 0;        
	//必须实现重心获取
	virtual Vector3 GetBarycentre() const  = 0; 
	virtual Color GetTexture(Crash) const {return Color(1, 1, 1);}
};


