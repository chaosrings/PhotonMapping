#pragma once
#include "vector3.h"
#include "color.h"
#include "bmp.h"
#include <vector>
class Camera
{
private:
	Vector3 eyePosition, lookAt, dw, dh;
	float lensW, lensH;
	int W, H;
	std::vector<std::vector<Color> >  data;
	std::string outFileName;
public:
	Camera(Vector3 _eyePos = Vector3(-2.f, 2.f, 0.5f),
		Vector3 _lookat = Vector3(0.6f, 1.f, -0.6f).GetUnitVector(),
		size_t _imageH = 760, size_t _imageW = 1280,
		float _lensH = 0.6f, float  _lensW = 1.0f)
		:eyePosition(_eyePos),
		lookAt(_lookat),
		lensH(_lensH), lensW(_lensW),
		H(_imageH), W(_imageW)
	{
		data.resize(H, std::vector<Color>(W, Color()));

		lookAt = lookAt.GetUnitVector();
		dw = lookAt.GetAnVerticalVector();
		dh = dw * lookAt;
		dw = dw * lensW / 2;
		dh = dh * lensH / 2;      //BMP图片的(0,0)在左下角，向上，向右遍历

		outFileName = "result.bmp";
	}
	~Camera() {}

	int GetH() { return H; }
	int GetW() { return W; }
	float GetLensH() { return lensH; }
	float GetLensW() { return lensW; }
	Vector3 GetEyePosition() { return eyePosition; }
	Vector3 GetLookAt() { return lookAt; }
	void SetH(int h) { H = h; }
	void SetW(int w) { W = w; }
	void SetLensH(float lh) { lensH = lh; }
	void SetLensW(float lw) { lensW = lw; }
	void SetEyePosition(Vector3 pos) { eyePosition = pos; }
	void SetLookAt(Vector3 lookat) { lookAt = lookat; }
	void SetOutFile(std::string filename) { outFileName = filename; }
	Vector3 Emit(float i, float j);//发射光线
	void Output(Bmp*);
	void SetColor(size_t i, size_t j, Color color) { data[i][j] = color; }
};