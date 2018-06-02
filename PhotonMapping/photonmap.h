#pragma once
#include "vector3.h"
#include "color.h"
#include <vector>
#include <queue>
using std::vector;
class Photon
{
public:
	Vector3 pos;
	Vector3 dir;
	Color power;
	int splitPlane;
	Photon(Vector3 Pos = Vector3(), Vector3 Dir = Vector3(), Color Power = Color(), int splitplane = 3) :pos(Pos), dir(Dir), power(Power), splitPlane(splitplane) {}
};
struct KDTreeNode
{
	Photon photon;
	KDTreeNode* left;
	KDTreeNode* right;
	KDTreeNode(Photon P = Photon(), KDTreeNode* l = nullptr, KDTreeNode* r = nullptr) :photon(P), left(l), right(r) {}
};
class PhotonMap
{
private:
	int storedPhotons;
	int emitPhotons;
	vector<Photon> photons;
	
	void makeEmpty(KDTreeNode* & t);
	KDTreeNode* BuildTree(int left, int right, int depth);//根据photons的left，right构建KD树,depth用于判断用x,y,z那一轴分割
public:
	KDTreeNode* root;
	PhotonMap() { root = nullptr; emitPhotons = 0; storedPhotons = 0; }
	~PhotonMap() { makeEmpty(root); photons.clear();  }
	int GetStoredPhotons() { return storedPhotons; }
	void SetEmitPhotons(int n) { emitPhotons = n; }
	int GetEmitPhotons() { return emitPhotons; }
	void LocatePhotons(KDTreeNode* t, Vector3& pos, float maxDist2, std::vector<Photon>& result);
	void Setup() { root = BuildTree(0, photons.size() - 1, 0); photons.clear(); }
	void Store(const Photon& photon) { photons.push_back(photon); ++storedPhotons;}
	Color GetIrradiance(Vector3& pos, Vector3& normal, float maxDist);

};