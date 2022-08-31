#pragma once
#include<array>
#include<Vector.hpp>
class Vertex {
public:
	Vertex(Vector3f& v) : pos(v), col({255, 255, 255}) { }
	Vertex(Vector3f& v, Vector3f& c) : pos(v), col(c) { }
	Vertex(float* v, float* c) : pos(v), col(c) { }
	Vertex(std::vector<float>& v) : pos(v), col({ 255, 255, 255 }) { }
public:
	Vector3f pos;
	Vector3f col;
};
class Triangle {
public:
	Triangle(Vertex vert0, Vertex vert1, Vertex vert2) : v0(vert0), v1(vert1), v2(vert2) { }
	Vertex v0, v1, v2;
};