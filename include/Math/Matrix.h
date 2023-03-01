#pragma once
#include <array>

#include "Vector.h"

class Comma_buffer;
class Matrix4d {
public:
	Matrix4d() : _arr{} {}
	Matrix4d(std::array<std::array<double, 4>, 4> arr) : _arr(arr) {}
	const std::array<double, 4> &operator[](const int i) const { return _arr[i]; }
	std::array<double, 4> &operator[](const int i) { return _arr[i]; }

	Vector4f operator*(const Vector4f &) const;
	Matrix4d operator*(const Matrix4d &rhs) const;
	static Matrix4d Identity() { return identity; };
	Matrix4d transpose() const;
	void swap_row(int i, int j);
	Matrix4d inverse() const;

private:
	std::array<std::array<double, 4>, 4> _arr;
	static std::array<std::array<double, 4>, 4> identity;
};

class Comma_buffer {
public:
	Comma_buffer(Matrix4d &m) : _m(m) {}
	Comma_buffer &operator,(double num) {
		_m[count / 4][count % 4] = num;
		++count;
		return *this;
	}
	~Comma_buffer() noexcept(false) {
		if (count != 16) {
			std::cerr <<
			          "Too few coefficients passed to comma initializer (operator<<)"
			          << std::endl;
			throw std::runtime_error("too few elements");
		}
	}
private:
	Matrix4d &_m;
	int count = 1;
};

Comma_buffer operator<<(Matrix4d &, double);
std::ostream &operator<<(std::ostream &os, const Matrix4d &rhs);