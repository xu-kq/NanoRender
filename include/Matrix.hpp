#pragma once
#include"Vector.hpp"
#include<array>

class Comma_buffer;
class Matrix4f {
public:
	Matrix4f() : _arr{} {}
	Matrix4f(std::array<std::array<float, 4>, 4> arr) : _arr(arr) { }
	const std::array<float, 4>& operator[](const int i) const { return _arr[i]; }
	std::array<float,4>& operator[](const int i) { return _arr[i]; }

	Vector4f operator*(const Vector4f&) const;
	Matrix4f operator*(const Matrix4f& rhs) const;

	static Matrix4f Identity() {
		return identity;
	};

private:
	std::array<std::array<float, 4>, 4> _arr;
	static std::array<std::array<float, 4>, 4> identity;
};


class Comma_buffer {
public:
	Comma_buffer(Matrix4f& m) : _m(m) { }
	Comma_buffer& operator,(float num) {
		_m[count / 4][count % 4] = num;
		++count;
		return *this;
	}
	~Comma_buffer() {
		if (count != 16) {
			std::cerr << 
				"Too few coefficients passed to comma initializer (operator<<)" 
				<< std::endl;
			throw std::runtime_error("too few elements");
		}
	}
private:
	Matrix4f& _m;
	int count = 1;
};

Comma_buffer operator<<(Matrix4f&, float);
std::ostream& operator<<(std::ostream& os, const Matrix4f& rhs);