#pragma once
#include <cmath>
#include <iomanip>
#include <initializer_list>
#include <iostream>
#include <vector>

class Vector2i {
public:
	Vector2i() = default;
	Vector2i(std::initializer_list<int> &il) {
		int i = 0;
		for (const auto &num : il) {
			this->operator[](i++) = num;
		}
	}
	Vector2i(const int xx, const int yy) : _x(xx), _y(yy) {}

	const int x() const { return _x; }
	const int y() const { return _y; }

	int &operator[](const int i) { return (&_x)[i]; }
	const int &operator[](const int i) const { return (&_x)[i]; }
private:
	int _x, _y;
};

class Vector2d {
public:
	Vector2d() = default;
	Vector2d(std::initializer_list<double> &il) {
		int i = 0;
		for (const auto &num : il) {
			this->operator[](i++) = num;
		}
	}
	Vector2d(const double xx, const double yy) : _x(xx), _y(yy) {}
	Vector2d(std::vector<double> &arr) : _x(arr[0]), _y(arr[1]) {}

	const double x() const { return _x; }
	const double y() const { return _y; }

	double &operator[](const int i) { return (&_x)[i]; }
	const double &operator[](const int i) const { return (&_x)[i]; }
private:
	double _x, _y;
};

class Vector3d {
public:
	Vector3d() = default;
	Vector3d(std::initializer_list<double> &il) {
		int i = 0;
		for (const auto &num : il) {
			this->operator[](i++) = num;
		}
	}
	Vector3d(const double xx, const double yy, const double zz) : _x(xx), _y(yy), _z(zz) {}
	Vector3d(std::vector<double> &arr) : _x(arr[0]), _y(arr[1]), _z(arr[2]) {}

	double &x() { return _x; }
	double &y() { return _y; }
	double &z() { return _z; }
	const double x() const { return _x; }
	const double y() const { return _y; }
	const double z() const { return _z; }

	double &operator[](const int i) { return (&_x)[i]; }
	const double &operator[](const int i) const { return (&_x)[i]; }

	const double dot(const Vector3d &) const;
	const Vector3d cross(const Vector3d &) const;
	const double norm() const;
	Vector3d cwsiseProduct(const Vector3d &) const;
	Vector3d normalized() const;
	Vector3d operator+(const Vector3d &) const;
	Vector3d operator-(const Vector3d &) const;
	Vector3d operator/(const double) const;
private:
	double _x, _y, _z;
};
Vector3d operator*(const Vector3d &, const double);
Vector3d operator*(const double, const Vector3d &);

class Vector4f {
public:
	Vector4f() : _x(0), _y(0), _z(0), _w(0) {}
	Vector4f(std::initializer_list<double> &il) {
		int i = 0;
		for (const auto &num : il) {
			this->operator[](i++) = num;
		}
	}
	Vector4f(const double xx, const double yy, const double zz, const double ww) :
			_x(xx), _y(yy), _z(zz), _w(ww) {}

	double x() const { return _x; }
	double y() const { return _y; }
	double z() const { return _z; }
	double w() const { return _w; }

	const Vector4f &operator/(double div) {
		_x /= div;
		_y /= div;
		_z /= div;
		_w /= div;
		return *this;
	}
	double &operator[](const int i) { return (&_x)[i]; }
	const double &operator[](const int i) const { return (&_x)[i]; }

	const double dot(const Vector4f &) const;
	const double norm() const;

private:
	double _x, _y, _z, _w;
};

std::ostream &operator<<(std::ostream &, const Vector3d &);
std::ostream &operator<<(std::ostream &, const Vector4f &);
const Vector3d to_vec3(const Vector4f &);
const Vector4f to_vec4(const Vector3d &, double w = 1.f);