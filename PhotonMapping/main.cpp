#pragma once
#include "photonmap.h"
#include <random>
#include <iostream>
#include <time.h>
int main()
{
	PhotonMap p;
	using namespace std;
	default_random_engine e;
	uniform_real_distribution<float> u(0, 100);
	for (int i = 0; i < 1000000; ++i)
	{
		p.Store(Photon(Vector3(u(e), u(e), u(e)), Vector3(), Color(), 3));
	}
	time_t begin = time(nullptr);
	p.Setup();
	time_t endT = time(nullptr);
	cout << endT - begin << endl;

	begin = time(nullptr);
	for (int c = 0; c < 10000000; ++c)
	{
		vector<Photon> ans;
		p.LocatePhotons(p.root, Vector3(u(e),u(e),u(e)), 1, ans);
	}
	endT = time(nullptr);
	cout << float(endT - begin) / 1000000 << endl;
	system("pause");
	return 0;
}