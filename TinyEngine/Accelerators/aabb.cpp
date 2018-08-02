#include "aabb.h"
bool AABB::Hit(Ray ray)
{
	double planeIn[3];
	double planeOut[3];
	//遍历x,y,z	
	for (int i = 0; i < 3; ++i)
	{
		double curAxisValue = ray.origin.GetCoord(i);
		double minAxisValue = minCoord.GetCoord(i);
		double maxAxisValue = maxCoord.GetCoord(i);
		//如果光线在某一轴的分量近乎0
		if (abs(ray.direction.GetCoord(i)) < EPS)
		{
			//并且原点不在包围盒内，必然不相交
			if (curAxisValue<minAxisValue || curAxisValue>maxAxisValue)
				return false;
			else
			{
				//原点在包围盒内便跳过对该轴的检测
				planeIn[i] = -INF;
				planeOut[i] = INF;
				continue;
			}
		}
		//下面是SlabMethod
		if (ray.direction.GetCoord(i) < EPS)
		{
			planeOut[i] = (minAxisValue - ray.origin.GetCoord(i)) / ray.direction.GetCoord(i);
			planeIn[i] = (maxAxisValue - ray.origin.GetCoord(i)) / ray.direction.GetCoord(i);
		}
		else
		{
			planeOut[i] = (maxAxisValue - ray.origin.GetCoord(i)) / ray.direction.GetCoord(i);
			planeIn[i] = (minAxisValue - ray.origin.GetCoord(i)) / ray.direction.GetCoord(i);
		}
	}
	double in_max = std::max(std::max(planeIn[0], planeIn[1]), planeIn[2]);
	double out_min = std::min(std::min(planeOut[0], planeOut[1]), planeOut[2]);
	return in_max < out_min;
}
void AABB::Extend(AABB another)
{
	for (int i = 0; i < 3; ++i)
	{
		this->minCoord.GetCoord(i) = std::min(this->minCoord.GetCoord(i), another.minCoord.GetCoord(i));
		this->maxCoord.GetCoord(i) = std::max(this->maxCoord.GetCoord(i), another.maxCoord.GetCoord(i));
	}
}
int AABB::GetLongestAxis()
{
	int longestAxis = 0;
	double maxDistance = -INF;
	for (int i = 0; i < 3; ++i)
	{
		double curDistance= maxCoord.GetCoord(i) - minCoord.GetCoord(i);
		if (curDistance > maxDistance)
		{
			maxDistance = curDistance;
			longestAxis = i;
		}
	}
	return longestAxis;
}