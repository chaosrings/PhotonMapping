#pragma once
#include "camera.h"
#include "light.h"
#include "bmp.h"
#include "vector3.h"
#include "primitive.h"
#include "common.h"
#include <vector>
#include <string>
using std::vector;
class Scene
{
private:
	vector<Primitive*> objects;
	vector<Light *>  lights;
	Camera camera;
public:
	Scene();
	~Scene();
	void Initialize();
	int GetImageH() { return camera.GetH(); }
	int GetImageW() { return camera.GetW(); }
	const vector<Light*> GetLights() { return lights; }
	const vector<Primitive*> GetObjects() { return objects; }
	Primitive* FindNearestObject(Vector3 origin, Vector3 direction);
	Crash     GetFirstCrash(Vector3 origin, Vector3 direction);
	Light*     FindNearestLight(Vector3 origin, Vector3 direction);
	friend class PhotonTracer;
	friend class RayTracer;
};