#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>


class Vector2i {
public:
	Vector2i() = default;
	Vector2i(int xx, int yy) : _x(xx), _y(yy) { }

	int x() const { return _x; }
	int y() const { return _y; }

	int& operator[](const int i) { return (&_x)[i]; }
	const int& operator[](const int i) const { return (&_x)[i]; }
private:
	int _x, _y;
};

class Vector3f {
public:
	Vector3f() = default;
	Vector3f(float xx, float yy, float zz) : _x(xx), _y(yy), _z(zz) { }
	Vector3f(const float* arr) : _x(arr[0]), _y(arr[1]), _z(arr[2]) { }
	Vector3f(std::vector<float>& arr) : _x(arr[0]), _y(arr[1]), _z(arr[2]) { }
	float& x()  { return _x; }
	float& y()  { return _y; }
	float& z()  { return _z; }
	float x() const { return _x; }
	float y() const { return _y; }
	float z() const { return _z; }

	float& operator[](const int i) { return (&_x)[i]; }
	const float& operator[](const int i) const { return (&_x)[i]; }

	float dot(const Vector3f&) const;
	Vector3f cross(const Vector3f&) const;
	Vector3f cwsiseDot(float) const;
	Vector3f operator+(const Vector3f&) const;
	float norm() const;

private:
	float _x, _y, _z;
};


class Vector4f {
public:
	Vector4f() : _x(0), _y(0), _z(0), _w(0) { }
	Vector4f(float xx, float yy, float zz, float ww) : _x(xx), _y(yy), _z(zz), _w(ww) { }

	float x() const { return _x; }
	float y() const { return _y; }
	float z() const { return _z; }
	float w() const { return _w; }

	Vector4f& operator/(float div) {
		_x /= div;
		_y /= div;
		_z /= div;
		_w /= div;
		return *this;
	}
	float& operator[](const int i) { return (&_x)[i]; }
	const float& operator[](const int i) const { return (&_x)[i]; }

	float dot(const Vector4f&) const;
	float norm() const;

private:
	float _x, _y, _z, _w;
};

std::ostream& operator<<(std::ostream&, const Vector3f&);
std::ostream& operator<<(std::ostream&, const Vector4f&);
Vector4f to_vec4(const Vector3f& v);