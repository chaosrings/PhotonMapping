#pragma once

#include<sstream>
#include <algorithm>
#include "vector3.h"
class Color {
public:
	double r, g, b;

	Color(double R = 0, double G = 0, double B = 0) : r(R), g(G), b(B) {}
	~Color() {}
	Color& operator=(const Vector3& colorVec) { r = colorVec.x; g = colorVec.y; b = colorVec.z; return *this; }
	friend Color operator + (const Color&, const Color&);
	friend Color operator - (const Color&, const Color&);
	friend Color operator * (const Color&, const Color&);
	friend Color operator * (const Color&, double);
	friend Color operator / (const Color&, double);
	friend Color& operator += (Color&, const Color&);
	friend Color& operator -= (Color&, const Color&);
	friend Color& operator *= (Color&, double);
	friend Color& operator /= (Color&, double);
	Color Confine(); //luminance must be less than or equal to 1
	double Power();
	void Input(std::stringstream&);
};


