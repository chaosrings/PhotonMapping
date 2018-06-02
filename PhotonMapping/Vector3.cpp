#include "vector3.h"
#include<cmath>
#include<sstream>
#include<cstdlib>
#include<random>
#include <time.h>



Vector3 operator + (const Vector3& A, const Vector3& B) {
	return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}

Vector3 operator - (const Vector3& A, const Vector3& B) {
	return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

Vector3 operator * (const Vector3& A, float k) {
	return Vector3(A.x * k, A.y * k, A.z * k);
}

Vector3 operator / (const Vector3& A, float k) {
	return Vector3(A.x / k, A.y / k, A.z / k);
}

Vector3 operator * (const Vector3& A, const Vector3& B) {
	return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

Vector3& operator += (Vector3& A, const Vector3& B) {
	A = A + B;
	return A;
}

Vector3& operator -= (Vector3& A, const Vector3& B) {
	A = A - B;
	return A;
}

Vector3& operator *= (Vector3& A, float k) {
	A = A * k;
	return A;
}

Vector3& operator /= (Vector3& A, float k) {
	A = A / k;
	return A;
}

Vector3& operator *= (Vector3& A, const Vector3& B) {
	A = A * B;
	return A;
}

Vector3 operator - (const Vector3& A) {
	return Vector3(-A.x, -A.y, -A.z);
}

float Vector3::Dot(const Vector3& term) {
	return x * term.x + y * term.y + z * term.z;
}

float Vector3::Module2() {
	return x * x + y * y + z * z;
}

float Vector3::Module(){
	return sqrt(x * x + y * y + z * z);
}

float Vector3::Distance2(Vector3& term){
	return (term - *this).Module2();
}

float Vector3::Distance(Vector3& term) {
	return (term - *this).Module();
}

float Vector3::GetCoord(int axis){
	if (axis == 0) return x;
	if (axis == 1) return y;
	return z;
}

Vector3 Vector3::GetUnitVector() {
	return *this / Module();
}

void Vector3::AssRandomVector() {
	do {
		x = RandomRealZeroOne() - 1;
		y = RandomRealZeroOne() - 1;
		z = RandomRealZeroOne() - 1;
	} while (x * x + y * y + z * z > 1 || x * x + y * y + z * z < EPS);
	*this = GetUnitVector();
}

Vector3 Vector3::GetAnVerticalVector() {
	Vector3 ret = *this * Vector3(0, 0, 1);
	if (ret.IsZeroVector()) ret = Vector3(1, 0, 0);
	else ret = ret.GetUnitVector();
	return ret;
}

bool Vector3::IsZeroVector() {
	return fabs(x) < EPS && fabs(y) < EPS && fabs(z) < EPS;
}

void Vector3::Input(std::stringstream& fin) {
	fin >> x >> y >> z;
}

Vector3 Vector3::Reflect(Vector3 N) {
	return *this - N * (2 * Dot(N));
}

Vector3 Vector3::Refract(Vector3 N, float n) {
	Vector3 V = GetUnitVector();
	float cosI = -N.Dot(V), cosT2 = 1 - (n * n) * (1 - cosI * cosI);
	if (cosT2 > EPS) return V * n + N * (n * cosI - sqrt(cosT2));
	return V.Reflect(N);
}

Vector3 Vector3::Diffuse(Vector3 N) {
	float theta = RandomRealZeroOne() *2*PI;
	float random2 = RandomRealZeroOne();
	Vector3 z = N.GetUnitVector();
	Vector3 y;
	/*大于0.1 与y轴作叉积,小于0.1与x轴作叉积*/
	if (z.x > 0.1) 
 		y = z*Vector3(0, 1, 0);
	else
		y = z*Vector3(1, 0, 0);
	y = y.GetUnitVector();
	Vector3 x = z*y;
	/*三个单位正交的基底，在z正向的半球内随机选择一个方向漫反射*/
	return (x*cos(theta)*sqrt(random2) + y*sin(theta)*sqrt(random2) + z*(1 - random2)).GetUnitVector();
}

Vector3 Vector3::Rotate(Vector3 axis, float theta) {
	Vector3 ret;
	float cost = cos(theta);
	float sint = sin(theta);
	ret.x += x * (axis.x * axis.x + (1 - axis.x * axis.x) * cost);
	ret.x += y * (axis.x * axis.y * (1 - cost) - axis.z * sint);
	ret.x += z * (axis.x * axis.z * (1 - cost) + axis.y * sint);
	ret.y += x * (axis.y * axis.x * (1 - cost) + axis.z * sint);
	ret.y += y * (axis.y * axis.y + (1 - axis.y * axis.y) * cost);
	ret.y += z * (axis.y * axis.z * (1 - cost) - axis.x * sint);
	ret.z += x * (axis.z * axis.x * (1 - cost) - axis.y * sint);
	ret.z += y * (axis.z * axis.y * (1 - cost) + axis.x * sint);
	ret.z += z * (axis.z * axis.z + (1 - axis.z * axis.z) * cost);
	return ret;
}


