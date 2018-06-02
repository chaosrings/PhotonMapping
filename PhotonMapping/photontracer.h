#pragma once
#include "photonmap.h"
#include "Vector3.h"
#include "color.h"
#include "scene.h"
#include "common.h"
class PhotonTracer
{
private:
	Scene* scene;
	PhotonMap* photonmap;
public:
	PhotonTracer()
	{
		photonmap = new PhotonMap();
	}
	~PhotonTracer() { delete photonmap; }
	void SetScene(Scene* _scene) {scene = _scene;}
	Scene& GetScene() { return *scene; }
	void Run(Scene*);
	void PhotonTracing(Photon p, int depth);
	PhotonMap* GetPhotonMap() { return photonmap; }
};