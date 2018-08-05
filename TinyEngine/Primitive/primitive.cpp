#include "primitive.h"

Color Primitive::GetTexture(double u, double v) const
{
	if (material.texture.get() != nullptr)
	{
		//ÖØ¸´ÌùÍ¼
		if (u > 1)
			u = u - floor(u);
		if (v > 1)
			v = v - floor(v);
		return material.texture->GetSmoothColor(u, v);
	}
	return Color(1, 1, 1);
}