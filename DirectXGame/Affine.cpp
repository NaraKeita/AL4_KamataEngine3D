#include "Affine.h"

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotation, const Vector3& translation) {
	Vector3 scale_ = scale;

	Matrix4x4 RotateMatY = {
		cosf(rotation.y), 0, -sinf(rotation.y), 0,
		0, 1, 0, 0, 
		sinf(rotation.y), 0, cosf(rotation.y), 0,
		0, 0, 0, 1
	};

	Matrix4x4 TranslateMat = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translation.x, translation.y, translation.z, 1
	};

	Matrix4x4 ansMat = Multiply(RotateMatY,TranslateMat);
	return ansMat;
}
