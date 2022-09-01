#pragma once
#include"fragment.hpp"
#include"Matrix.hpp"
#include"Triangle.hpp"
#include<vector>
#include<algorithm>
#include<tuple>

enum DrawType { WIREFRAME, NORMAL, BLINNPHONG};

class Rasterizer {
public:
	Rasterizer(int width, int height, unsigned char* fb)
		: frame_buffer(fb), Width(width), Height(height),
		depth_buffer(size_t(Width)*Height, std::numeric_limits<float>::lowest()) {}

	void draw_wireframe(Triangle&);
	void draw_fragment(Triangle&);
	void draw(std::vector<Triangle*>&, DrawType);
	void set_model_matrix(const Matrix4f&);
	void set_view_matrix(const Matrix4f&);
	void set_projection_matrix(const Matrix4f&);
	void set_mv_inv_transpose();
	void flush();


private:
	const int Height = 700,
		Width = 700;
	unsigned char* frame_buffer;
	std::vector<float> depth_buffer;

	Matrix4f m;
	Matrix4f v;
	Matrix4f p;
	Matrix4f mv_inv_t;

	// Breseham Algorithm
	void plot_line(const Vector2i& start, const Vector2i& end, const Vector3f& color = Vector3f(255, 255, 255));
	void plot_line(const float x1, const float y1, const float x2, const float y2, 
		const Vector3f& color = Vector3f(255, 255, 255));

	// utility function
	void set_pixel(const int, const int, const Vector3f&);
	void set_pixel(const Vector2i&, const Vector3f&);
};