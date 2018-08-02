#pragma once
#include<cmath>
#include<sstream>
#include<cstdlib>
#include <time.h>
#include "common.h"

class Vector3 
{
public:
	double x, y, z;

	Vector3(double X = 0, double Y = 0, double Z = 0) : x(X), y(Y), z(Z) {}
	~Vector3() {}
	friend Vector3 operator + (const Vector3&, const Vector3&);
	friend Vector3 operator - (const Vector3&, const Vector3&);
	friend Vector3 operator * (const Vector3&, double);
	friend Vector3 operator / (const Vector3&, double);
	friend Vector3 operator * (const Vector3&, const Vector3&); //cross product
	friend Vector3& operator += (Vector3&, const Vector3&);
	friend Vector3& operator -= (Vector3&, const Vector3&);
	friend Vector3& operator *= (Vector3&,  double);
	friend Vector3& operator /= (Vector3&,  double);
	friend Vector3& operator *= (Vector3&, const Vector3&);
	friend Vector3 operator - (const Vector3&);
	double Dot(const Vector3&) const;
	double Module2() const;
	double Module() const;
	double Distance2(Vector3&) const;
	double Distance(Vector3&) const ;
	double IncludedAngle(Vector3 v2);
	double& GetCoord(int axis);
	double  GetCoord(int axis) const;
	Vector3 GetUnitVector() const;
	void AssRandomVector();
	Vector3 GetAnVerticalVector() const;
	bool IsZeroVector() const;
	Vector3 Reflect(Vector3 N) const;
	Vector3 Refract(Vector3 N, double n) const;
	Vector3 Diffuse(Vector3 normal) const;
};


double IncludedAngle(Vector3, Vector3);