#include "photonmap.h"


void PhotonMap::makeEmpty(KDTreeNode*& t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}
KDTreeNode* PhotonMap::BuildTree(int left, int right, int depth)
{
	if (left > right)
		return nullptr;
	else if (left == right)
	{
		KDTreeNode* t = new KDTreeNode(photons[left]);
		t->photon.splitPlane = 3;
		return t;
	}
	std::sort(photons.begin()+left,photons.begin()+right+1,
		[depth](const Photon& p1,const Photon &p2)
	{
		if (depth % 3 == 0)
			return p1.pos.x < p2.pos.x;
		else if (depth % 3 == 1)
			return p1.pos.y < p2.pos.y;
		return p1.pos.z < p2.pos.z;
	});
	int mid = (left + right) / 2;
	KDTreeNode* t = new KDTreeNode(photons[mid]);
	t->photon.splitPlane = depth%3; //0 :x 1:y 2:z
	t->left = BuildTree(left, mid - 1, depth + 1);
	t->right = BuildTree(mid + 1, right, depth + 1);
	return t;
}

void  PhotonMap::LocatePhotons(KDTreeNode* t,Vector3& pos , float maxDist2,std::vector<Photon>& result)
{
	if (t == nullptr)
		return;
	else if (t->photon.splitPlane == 3)
	{
		double distToPos = pos.Distance2(t->photon.pos);
		if (distToPos < maxDist2)
			result.push_back(t->photon);
		return;
	}
	//pos.splitCoord<t.splitCoord ����������,�������������ң�ֱ��Ҷ�ڵ�
	int splitPlane = t->photon.splitPlane;
	if (pos.GetCoord(splitPlane) < t->photon.pos.GetCoord(splitPlane))
		LocatePhotons(t->left, pos, maxDist2, result);
	else if (pos.GetCoord(splitPlane) > t->photon.pos.GetCoord(splitPlane))
		LocatePhotons(t->right, pos, maxDist2, result);
	//�Ӻ��ӽ����ݺ��ж�t��pos�ľ��롣
	float curDist2 = pos.Distance2(t->photon.pos);   
	/*�����ǰ���ľ����maxDist����ô��ǰ���û�в��ҵĺ���(���pos.splitCoord>t->photon.splitCoord)
	��Ȼ���벻���ܱ�maxDistС*/
	if (curDist2 > maxDist2)  
		return;
	result.push_back(t->photon);
	KDTreeNode* nextSearch = t->left;
	if (pos.GetCoord(splitPlane) < t->photon.pos.GetCoord(splitPlane))  //�����������ݣ�����������
		nextSearch = t->right;
	LocatePhotons(nextSearch, pos, maxDist2, result);
}
Color PhotonMap::GetIrradiance(Vector3& pos, Vector3& normal, float maxDist)
{
	Color ret;
	vector<Photon> result;
	LocatePhotons(root, pos, maxDist*maxDist, result);
	if (result.size() <= 8)
		return ret;

	for (int i = 0; i <(int) result.size(); ++i)
	{
		if (normal.Dot(result[i].dir) < 0)
			ret += result[i].power;
	}
	ret /=(PI*maxDist*maxDist*emitPhotons);
	return ret;
}
