#include "color.h"
Color operator + (const Color& A, const Color& B) {
	return Color(A.r + B.r, A.g + B.g, A.b + B.b);
}

Color operator - (const Color& A, const Color& B) {
	return Color(A.r - B.r, A.g - B.g, A.b - B.b);
}

Color operator * (const Color& A, const Color& B) {
	return Color(A.r * B.r, A.g * B.g, A.b * B.b);
}

Color operator * (const Color& A, float k) {
	return Color(A.r * k, A.g * k, A.b * k);
}

Color operator / (const Color& A, float k) {
	return Color(A.r / k, A.g / k, A.b / k);
}

Color& operator += (Color& A, const Color& B) {
	A = A + B;
	return A;
}

Color& operator -= (Color& A, const Color& B) {
	A = A - B;
	return A;
}

Color& operator *= (Color& A, float k) {
	A = A * k;
	return A;
}

Color& operator /= (Color& A, float k) {
	A = A / k;
	return A;
}

Color Color::Confine() {
	return Color(std::min(r, 1.0f), std::min(g, 1.0f), std::min(b, 1.0f));
}

float Color::Power() {
	return (r + g + b) / 3;
}

void Color::Input(std::stringstream& fin) {
	fin >> r >> g >> b;
}
