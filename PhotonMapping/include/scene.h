#pragma once
#include "camera.h"
#include "light.h"
#include "bmp.h"
#include "vector3.h"
#include "primitive.h"
#include "common.h"
#include <vector>
#include <string>
#include <memory>
using std::vector;
using std::shared_ptr;
class Scene
{
private:
	vector<shared_ptr<Primitive> > objects;
	vector<shared_ptr<Light>>  lights;
	shared_ptr<Camera> camera;
public:
	Scene();
	~Scene();
	int GetImageH() { return camera->GetH(); }
	int GetImageW() { return camera->GetW(); }
	const vector<shared_ptr<Light>> GetLights() { return lights; }
	const vector<shared_ptr<Primitive>>  GetObjects() { return objects; }
	shared_ptr<Primitive> FindNearestObject(Vector3 origin, Vector3 direction);
	Crash GetFirstCrash(Vector3 origin, Vector3 direction);
	shared_ptr<Light>     FindNearestLight(Vector3 origin, Vector3 direction);
	void SetCamera(shared_ptr<Camera> _camera) { camera = _camera; }
	void AddObject(shared_ptr<Primitive> _obj) { objects.push_back(_obj); }
	void AddLight(shared_ptr<Light> _light) { lights.push_back(_light); }
	friend class PhotonTracer;
	friend class RayTracer;
};