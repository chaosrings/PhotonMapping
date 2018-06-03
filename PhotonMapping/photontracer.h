#ifndef PHOTONTRACER
#define PHOTONTRACER

#include"scene.h"
#include"photonmap.h"


class PhotonTracer {
	Scene* scene;
	PhotonMap* photonmap;

	void PhotonTracing(Photon, int dep);
	bool PhotonDiffusion(Crash crash, Primitive * pri, Photon photon, int dep, double * prob);
	bool PhotonReflection(Crash crash, Primitive * pri, Photon photon, int dep, double * prob);
	bool PhotonRefraction(Crash crash, Primitive * pri, Photon photon, int dep, double * prob);

public:
	PhotonTracer() {};
	void SetScene(Scene* input) { scene = input; }
	PhotonMap* GetPhotonMap() { return photonmap; }
	void Run(Scene*);
};

#endif
