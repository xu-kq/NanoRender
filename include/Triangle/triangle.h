#pragma once
#include <array>

#include <Math/Vector.h>

class Vertex {
public:
	Vertex(const Vector3d &p, const Vector2d &t, const Vector3d &n)
			: position(p), texture(t), normal(n) {}
public:
	Vector3d position;
	Vector2d texture;
	Vector3d normal;
};

class Triangle {
public:
	Triangle(const Vertex &vert0, const Vertex &vert1, const Vertex &vert2)
			: v0(vert0), v1(vert1), v2(vert2) {}
	Triangle(std::vector<Vertex> &vlists) : v0(vlists[0]), v1(vlists[1]), v2(vlists[2]) {}
	Vertex v0, v1, v2;
};