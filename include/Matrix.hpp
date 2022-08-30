#pragma once
#include"Vector.hpp"
#include<array>

class Matrix4f {
public:
	Matrix4f() : arr{} {}
	const std::array<float, 4>& operator[](const int i) const { return arr[i]; }
	std::array<float,4>& operator[](const int i) { return arr[i]; }

	Vector4f Matrix4f::operator*(const Vector4f&) const;
	Matrix4f Matrix4f::operator*(const Matrix4f& rhs) const;
private:
	std::array<std::array<float, 4>, 4> arr;
};

std::ostream& operator<<(std::ostream& os, const Matrix4f& rhs) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			os << std::setprecision(4) << rhs[i][j] << "\t";
		}
		os << std::endl;
	}
	return os;
}