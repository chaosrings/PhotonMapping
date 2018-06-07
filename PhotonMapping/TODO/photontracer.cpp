#include"photontracer.h"
#include"scene.h"
#include<cstdlib>
#include<iostream>
#define ran() ( double( rand() % RAND_MAX ) / RAND_MAX )


bool PhotonTracer::PhotonDiffusion(Crash crash, Primitive* pri, Photon photon, int dep, double* prob) {
	Material material = pri->GetMaterial();
	double eta = (material.diff + material.refl) * material.color.Power();

	if (eta <= RandomRealZeroOne() * (*prob)) {
		*prob -= eta;
		return false;
	}

	photon.dir = crash.normal.Diffuse(crash.normal);
	photon.power = photon.power * material.color / material.color.Power();
	PhotonTracing(photon, dep + 1);
	return true;
}

bool PhotonTracer::PhotonReflection(Crash crash, Primitive* pri, Photon photon, int dep, double* prob) {
	Material material = pri->GetMaterial();
	double eta = material.refl * material.color.Power();

	if (eta <= RandomRealZeroOne() * (*prob)) {
		*prob -= eta;
		return false;
	}

	photon.dir = photon.dir.Reflect(crash.normal);
	photon.power = photon.power * material.color / material.color.Power();
	PhotonTracing(photon, dep + 1);
	return true;
}

bool PhotonTracer::PhotonRefraction(Crash crash, Primitive* pri, Photon photon, int dep, double* prob) {
	Material material = pri->GetMaterial();
	double eta = material.refr;
	if (crash.front == false) {
		Color absor = material.absor * crash.dist;
		Color trans = Color(exp(absor.r), exp(absor.g), exp(absor.b));
		eta *= trans.Power();
		photon.power = photon.power * trans / trans.Power();
	}

	if (eta <= RandomRealZeroOne() * (*prob)) {
		*prob -= eta;
		return false;
	}

	double n = material.rindex;
	if (crash.front) n = 1.0f / n;
	photon.dir = photon.dir.Refract(crash.normal, n);
	PhotonTracing(photon, dep + 1);
	return true;
}

void PhotonTracer::PhotonTracing(Photon photon, int dep) {
	if (dep > maxPhotonTracingDepth) return;
	Primitive* nearest_primitive = scene->FindNearestObject(photon.pos, photon.dir);

	
	if (nearest_primitive != NULL) {
		Crash crash = nearest_primitive->Collide(photon.pos, photon.dir);
		photon.pos = crash.position;
		if (nearest_primitive->GetMaterial().diff > EPS&&dep>1)
		{
			if(photonmap->GetStoredPhotons()<maxEmitPhoton)
				photonmap->Store(photon);
		}
		double prob = 1;
		if (PhotonDiffusion(crash,nearest_primitive, photon, dep, &prob) == false)
			if (PhotonReflection(crash,nearest_primitive, photon, dep, &prob) == false)
				if (PhotonRefraction(crash,nearest_primitive, photon, dep, &prob) == false);
	}
}

void PhotonTracer::Run(Scene* _scene ) {
	int n = maxEmitPhoton;
	photonmap = new Photonmap(n);
	photonmap->SetEmitPhotons(n);
	scene = _scene;
	double total_power = 0;
	for(auto light :scene->GetLights())
		total_power += light->GetColor().Power();
	double photon_power = total_power / n;

	int emited_photons = 0;
	for (auto light : scene->GetLights()) {
		double light_power = light->GetColor().Power();
		while (light_power >= photon_power) {
			if ((++emited_photons & 1048575) == 0) std::cout << "Emited photons: " << emited_photons << std::endl;
			//Photon photon = light->EmitPhoton();
			photon.power *= total_power;
			PhotonTracing(photon, 1);
			light_power -= photon_power;
		}
		std::cout << "Stored photons: " << photonmap->GetStoredPhotons() << std::endl;
	}


	std::cout << "Tree balancing..." << std::endl;
	photonmap->Balance();
}
