#include "photontracer.h"
#include <iostream>

void PhotonTracer::Run(Scene* _scene)
{
	scene = _scene;
	int emitedPhoton = 0;
	photonmap->SetEmitPhotons(maxEmitPhoton);
	int emited = 0;
	while (emited<maxEmitPhoton)
	{
		for (auto light : scene->GetLights())
		{
			Photon emitOne = light->EmitPhoton();
		 	PhotonTracing(emitOne,0);
		}
		++emited;
	}
	photonmap->Setup();
	std::cout << "photon map setup\n";
	
}

void PhotonTracer::PhotonTracing(Photon p, int depth)
{
	if (depth > maxPhotonTracingDepth)
		return;
	Primitive* collideObject = scene->FindNearestObject(p.pos, p.dir);
	if (collideObject != nullptr)
	{
		Crash crash = collideObject->Collide(p.pos, p.dir);
		if (collideObject->GetMaterial().diff > EPS&&depth > 1)
		{
			p.pos = crash.position;
			photonmap->Store(p);
		}
		float delta = RandomRealZeroOne();
		float avgFactor = collideObject->GetMaterial().color.Power();
		if (avgFactor < EPS)
			return;
		float diffAvgFactor = collideObject->GetMaterial().diff;
		float refrAvgFactor = collideObject->GetMaterial().refr;
		float reflAvgFactor = collideObject->GetMaterial().refl;

		p.power = p.power*collideObject->GetMaterial().color/avgFactor;
		p.pos = crash.position;
		if (delta < diffAvgFactor)
		{
			p.dir = p.dir.Diffuse(crash.normal);
		}
		else if (delta > diffAvgFactor&&delta < diffAvgFactor + refrAvgFactor)
		{
			float n = collideObject->GetMaterial().rindex;
			if (crash.front)
				n = 1 / n;
			p.dir = p.dir.Refract(crash.normal, n);
		}
		else if (delta > diffAvgFactor + refrAvgFactor&&delta < diffAvgFactor + refrAvgFactor + reflAvgFactor)
		{
			p.dir = p.dir.Reflect(crash.normal);
		}
		else
			return;
		PhotonTracing(p, depth + 1);
	}
	
}