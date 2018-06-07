#pragma once
#include "vector3.h"
#include "color.h"
#include "bmp.h"
#include <vector>
class Camera
{
	Vector3 eyePosition, normal, dw, dh;
	float lensW, lensH;
	int W, H;
	std::vector<std::vector<Color> >  data;
public:
	Camera(Vector3 _eyePos = Vector3(-2.f, 2.f, 0.5f),
		Vector3 _normal = Vector3(0.6f, 1.f, -0.6f).GetUnitVector(),
		size_t _imageH = 760, size_t _imageW = 1280,
		float _lensH = 0.6f, float  _lensW = 1.0f)
		:eyePosition(_eyePos),
		normal(_normal),
		lensH(_lensH), lensW(_lensW),
		H(_imageH), W(_imageW)
	{
		data.resize(H, std::vector<Color>(W, Color()));

		normal = normal.GetUnitVector();
		dw = normal.GetAnVerticalVector();
		dh = dw * normal;
		dw = dw * lensW / 2;
		dh = dh * lensH / 2;      //BMP图片的(0,0)在左下角，向上，向右遍历
	}
	~Camera() {}

	int GetH() { return H; }
	int GetW() { return W; }
	Vector3 Emit(float i, float j);//发射光线
	void Output(Bmp*);
	void SetColor(size_t i, size_t j, Color color) { data[i][j] = color; }
	Vector3 GetEyePosition() { return eyePosition; }
};