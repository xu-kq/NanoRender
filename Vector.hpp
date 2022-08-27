#pragma once

#include<iostream>
#include<vector>
#include<cmath>

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

std::ostream& operator<<(std::ostream& os, Vector3f v) {
	os << v[0] << "\n" << v[1] << "\n" << v[2];
	return os;
}

float Vector3f::dot(const Vector3f& rhs) const {
	return _x * rhs.x() + _y * rhs.y() + _z * rhs.z();
}

float Vector3f::norm() const {
	return std::sqrt(this->dot(*this));
}

Vector3f Vector3f::cross(const Vector3f& rhs) const {

	Vector3f res;
	res[0] = _y * rhs.z() - _z * rhs.y();
	res[1] = _z * rhs.x() - _x * rhs.z();
	res[2] = _x * rhs.y() - _y * rhs.x();
	return res;
}



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

std::ostream& operator<<(std::ostream& os, Vector4f v) {
	os << v[0] << "\n" << v[1] << "\n" << v[2] << "\n" << v[3] << std::endl;
	return os;
}

float Vector4f::dot(const Vector4f& rhs) const {
	return _x * rhs.x() + _y * rhs.y() + _z * rhs.z() + _w * rhs.w();
}

float Vector4f::norm() const {
	return std::sqrt(this->dot(*this));
}