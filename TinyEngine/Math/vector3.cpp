
#include "vector3.h"
Vector3 operator + (const Vector3& A, const Vector3& B) {
	return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}

Vector3 operator - (const Vector3& A, const Vector3& B) {
	return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

Vector3 operator * (const Vector3& A, double k) {
	return Vector3(A.x * k, A.y * k, A.z * k);
}

Vector3 operator / (const Vector3& A, double k) {
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

Vector3& operator *= (Vector3& A, double k) {
	A = A * k;
	return A;
}

Vector3& operator /= (Vector3& A, double k) {
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

double Vector3::Dot(const Vector3& term) const {
	return x * term.x + y * term.y + z * term.z;
}

inline double Vector3::Module2() const {
	return x * x + y * y + z * z;
}

inline double Vector3::Module() const{
	return sqrt(x * x + y * y + z * z);
}

double Vector3::Distance2(Vector3& term) const{
	return (term - *this).Module2();
}

double Vector3::Distance(Vector3& term) const {
	return (term - *this).Module();
}

double Vector3::IncludedAngle(Vector3 v2)
{
	double costheta = (this->Dot(v2)) / (this->Module()*v2.Module());
	return acos(costheta);
}

double& Vector3::GetCoord(int axis){
	if (axis == 0) return x;
	if (axis == 1) return y;
	return z;
}
double Vector3::GetCoord(int axis) const{
	if (axis == 0) return x;
	if (axis == 1) return y;
	return z;
}
inline Vector3 Vector3::GetUnitVector() const {
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

Vector3 Vector3::GetAnVerticalVector() const {
	Vector3 ret = *this * Vector3(0, 0, 1);
	if (ret.IsZeroVector()) ret = Vector3(1, 0, 0);
	else ret = ret.GetUnitVector();
	return ret;
}

bool Vector3::IsZeroVector() const {
	return fabs(x) < EPS && fabs(y) < EPS && fabs(z) < EPS;
}

Vector3 Vector3::Reflect(Vector3 N) const {
	return *this - N * (2 * Dot(N));
}

Vector3 Vector3::Refract(Vector3 N, double n) const {
	Vector3 V = GetUnitVector();
	double cosI = -N.Dot(V), cosT2 = 1 - (n * n) * (1 - cosI * cosI);
	if (cosT2 > EPS) return V * n + N * (n * cosI - sqrt(cosT2));
	return V.Reflect(N);
}

Vector3 Vector3::Diffuse(Vector3 N)  const{
	double theta = RandomRealZeroOne() *2*PI;
	double random2 = RandomRealZeroOne();
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


Vector3 Vector3::RotateWithAxis(int axis, double angle) const
{
	Vector3 ans = *this;
	//x轴旋转
	if (axis == 0)
	{
		ans.y = y*cos(angle) + z*sin(angle);
		ans.z = y*(-sin(angle)) + z*cos(angle);
	}
	else if (axis == 1)
	{
		ans.x = x*cos(angle) + z*(-sin(angle));
		ans.z = x*sin(angle) + z*(cos(angle));
	}
	else
	{
		ans.x = x*cos(angle) + y*sin(angle);
		ans.y = x*(-sin(angle)) + y*cos(angle);
	}
	return ans;
}

