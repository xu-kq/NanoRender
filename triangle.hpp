#pragma once
#include<array>
#include<Vector.hpp>

class Triangle {
public:
	Triangle(const float* vert0, const float* vert1, const float* vert2)
		: _v0(vert0), _v1(vert1), _v2(vert2) { }
	Triangle(Vector3f vert0, Vector3f vert1, Vector3f vert2) : _v0(vert0), _v1(vert1), _v2(vert2) { }

	Vector3f& v0() { return _v0; }
	Vector3f& v1() { return _v1; }
	Vector3f& v2() { return _v2; }

	void show() {
		std::cout << _v0 << _v1 << _v2 << std::endl;
	}
private:
	Vector3f _v0, _v1, _v2;
};