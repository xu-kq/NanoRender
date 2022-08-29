#pragma once

#include<iostream>
#include <iomanip>
#include<vector>
#include<cmath>


class Vector2i {
public:
	Vector2i() = default;
	Vector2i(int xx, int yy) : _x(xx), _y(yy) { }

	float x() const { return _x; }
	float y() const { return _y; }

	float& operator[](const int i) { return (&_x)[i]; }
	const float& operator[](const int i) const { return (&_x)[i]; }
private:
	float _x, _y;
};
class Vector3f {
public:
	Vector3f() = default;
	Vector3f(float xx, float yy, float zz) : _x(xx), _y(yy), _z(zz) { }

	float x() const { return _x; }
	float y() const { return _y; }
	float z() const { return _z; }

	float& operator[](const int i) { return (&_x)[i]; }
	const float& operator[](const int i) const { return (&_x)[i]; }

	float dot(const Vector3f&) const;
	Vector3f cross(const Vector3f&) const;
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

	float& operator[](const int i) { return (&_x)[i]; }
	const float& operator[](const int i) const { return (&_x)[i]; }

	float dot(const Vector4f&) const;
	float norm() const;

private:
	float _x, _y, _z, _w;
};
