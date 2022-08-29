#pragma once
#include<lodepng.h>
#include"Matrix.hpp"
#include"Triangle.hpp"
#include<vector>

class Rasterizer {
public:
	Rasterizer() : Rasterizer(700, 700) { }
	Rasterizer(int width, int height)
		: Rasterizer("../../../image/output.png", width, height) { }
	Rasterizer(const char* filename, int width, int height)
		: Filename(new char[strlen(filename) + 1]),
		Width(width), Height(height), frame_buffer(4 * width * height) {
		memcpy(Filename, filename, strlen(filename) + 1);
	}
	Rasterizer(Rasterizer&) = delete;
	Rasterizer(Rasterizer&&) = delete;
	~Rasterizer() { 
		delete[] Filename; 
		Filename = nullptr; 
	}

	void rasterize(Triangle&);
	void show();

	void set_model_matrix(const Matrix4f&);
	void set_view_matrix(const Matrix4f&);
	void set_projection_matrix(const Matrix4f&);

private:
	char* Filename = nullptr;
	const int Height = 700,
		Width = 700;
	std::vector<unsigned char> frame_buffer;

	Matrix4f m;
	Matrix4f v;
	Matrix4f p;

	// Breseham Algorithm
	void plot_line(const Vector2i& start, const Vector2i& end, const Vector3f& color = Vector3f(255, 255, 255));
	void plot_line(float x1, float y1, float x2, float y2, const Vector3f& color = Vector3f(255, 255, 255));

	void plot_triangle_wireframe(Triangle&);

	// utility function
	void set_pixel(int, int, const Vector3f&);
	void set_pixel(const Vector2i&, const Vector3f&);
	void flush();
};