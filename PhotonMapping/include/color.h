#pragma once

#include<sstream>
#include <algorithm>
class Color {
public:
	float r, g, b;

	Color(float R = 0, float G = 0, float B = 0) : r(R), g(G), b(B) {}
	~Color() {}

	friend Color operator + (const Color&, const Color&);
	friend Color operator - (const Color&, const Color&);
	friend Color operator * (const Color&, const Color&);
	friend Color operator * (const Color&, float);
	friend Color operator / (const Color&, float);
	friend Color& operator += (Color&, const Color&);
	friend Color& operator -= (Color&, const Color&);
	friend Color& operator *= (Color&, float);
	friend Color& operator /= (Color&, float);
	Color Confine(); //luminance must be less than or equal to 1
	float Power();
	void Input(std::stringstream&);
};


