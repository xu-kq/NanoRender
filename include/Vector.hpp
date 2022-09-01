#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<initializer_list>

class Vector2i {
public:
	Vector2i() = default;
	Vector2i(std::initializer_list<int>& il) {
		int i = 0;
		for (const auto& num : il) {
			this->operator[](i++) = num;
		}
	}
	Vector2i(const int xx, const int yy) : _x(xx), _y(yy) { }

	const int x() const { return _x; }
	const int y() const { return _y; }

	int& operator[](const int i) { return (&_x)[i]; }
	const int& operator[](const int i) const { return (&_x)[i]; }
private:
	int _x, _y;
};

class Vector2f {
public:
	Vector2f() = default;
	Vector2f(std::initializer_list<float>& il) {
		int i = 0;
		for (const auto& num : il) {
			this->operator[](i++) = num;
		}
	}
	Vector2f(const float xx, const float yy) : _x(xx), _y(yy) { }

	const float x() const { return _x; }
	const float y() const { return _y; }

	float& operator[](const int i) { return (&_x)[i]; }
	const float& operator[](const int i) const { return (&_x)[i]; }
private:
	float _x, _y;
};

class Vector3f {
public:
	Vector3f() = default;
	Vector3f(std::initializer_list<float>& il) {
		int i = 0;
		for (const auto& num : il) {
			this->operator[](i++) = num;
		}
	}
	Vector3f(const float xx, const float yy, const float zz) : _x(xx), _y(yy), _z(zz) { }
	Vector3f(std::vector<float>& arr) : _x(arr[0]), _y(arr[1]), _z(arr[2]) { }
	
	float& x()  { return _x; }
	float& y()  { return _y; }
	float& z()  { return _z; }
	const float x() const { return _x; }
	const float y() const { return _y; }
	const float z() const { return _z; }

	float& operator[](const int i) { return (&_x)[i]; }
	const float& operator[](const int i) const { return (&_x)[i]; }

	const float dot(const Vector3f&) const;
	const Vector3f cross(const Vector3f&) const;
	const Vector3f cwsiseDot(float) const;
	const float norm() const;

private:
	float _x, _y, _z;
};
Vector3f operator+(const Vector3f&, const Vector3f&);


class Vector4f {
public:
	Vector4f() : _x(0), _y(0), _z(0), _w(0) { }
	Vector4f(std::initializer_list<float>& il) {
		int i = 0;
		for (const auto& num : il) {
			this->operator[](i++) = num;
		}
	}
	Vector4f(const float xx, const float yy, const float zz, const float ww) : 
		_x(xx), _y(yy), _z(zz), _w(ww) { }

	float x() const { return _x; }
	float y() const { return _y; }
	float z() const { return _z; }
	float w() const { return _w; }

	const Vector4f& operator/(float div) {
		_x /= div;
		_y /= div;
		_z /= div;
		_w /= div;
		return *this;
	}
	float& operator[](const int i) { return (&_x)[i]; }
	const float& operator[](const int i) const { return (&_x)[i]; }

	const float dot(const Vector4f&) const;
	const float norm() const;

private:
	float _x, _y, _z, _w;
};

std::ostream& operator<<(std::ostream&, const Vector3f&);
std::ostream& operator<<(std::ostream&, const Vector4f&);
const Vector4f to_vec4(const Vector3f& v);