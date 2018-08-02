#include "camera.h"


Vector3 Camera::Emit(double i, double j) {
	return lookAt + dh * (2 * i / H - 1) + dw * (2 * j / W - 1);
}
void Camera::Output(Bmp* bmp) {
	bmp->Initialize(H, W);

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			bmp->SetColor(i, j, data[i][j]);
}
