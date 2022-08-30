#include"Matrix.hpp"


Vector4f Matrix4f::operator*(const Vector4f& rhs) const {
	Vector4f ret;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ret[i] += arr[i][j] * rhs[j];
		}
	}
	return ret;
}

Matrix4f Matrix4f::operator*(const Matrix4f& rhs) const {
	Matrix4f ret;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				ret[i][j] += arr[i][k] * rhs[k][j];
			}
		}
	}
	return ret;
}