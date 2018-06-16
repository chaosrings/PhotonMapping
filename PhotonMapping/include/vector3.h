#pragma once
#include<cmath>
#include<sstream>
#include<cstdlib>
#include <time.h>
#include "common.h"

class Vector3 
{
public:
	float x, y, z;

	Vector3(float X = 0, float Y = 0, float Z = 0) : x(X), y(Y), z(Z) {}
	~Vector3() {}
	friend Vector3 operator + (const Vector3&, const Vector3&);
	friend Vector3 operator - (const Vector3&, const Vector3&);
	friend Vector3 operator * (const Vector3&, float);
	friend Vector3 operator / (const Vector3&, float);
	friend Vector3 operator * (const Vector3&, const Vector3&); //cross product
	friend Vector3& operator += (Vector3&, const Vector3&);
	friend Vector3& operator -= (Vector3&, const Vector3&);
	friend Vector3& operator *= (Vector3&,  float);
	friend Vector3& operator /= (Vector3&,  float);
	friend Vector3& operator *= (Vector3&, const Vector3&);
	friend Vector3 operator - (const Vector3&);
	float Dot(const Vector3&);
	float Module2();
	float Module();
	float Distance2(Vector3&);
	float Distance(Vector3&) ;
	float& GetCoord(int axis);
	Vector3 GetUnitVector();
	void AssRandomVector();
	Vector3 GetAnVerticalVector();
	bool IsZeroVector();
	Vector3 Reflect(Vector3 N);
	Vector3 Refract(Vector3 N, float n);
	Vector3 Diffuse(Vector3 normal);
};


float IncludedAngle(Vector3, Vector3);