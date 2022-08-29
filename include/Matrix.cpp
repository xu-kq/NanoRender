#include"Matrix.hpp"

Comma_buffer operator<<(Matrix4f& m, float num) {
	m[0][0] = num;
	return Comma_buffer(m);
}

std::ostream& operator<<(std::ostream& os, const Matrix4f& rhs) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			os << std::setprecision(4) << rhs[i][j] << "\t";
		}
		os << std::endl;
	}
	return os;
}

Vector4f Matrix4f::operator*(const Vector4f& rhs) const {
	Vector4f ret;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ret[i] += _arr[i][j] * rhs[j];
		}
	}
	return ret;
}

Matrix4f Matrix4f::operator*(const Matrix4f& rhs) const {
	Matrix4f ret;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				ret[i][j] += _arr[i][k] * rhs[k][j];
			}
		}
	}
	return ret;
}

std::array<std::array<float, 4>, 4> Matrix4f::identity = 
{	
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 
};