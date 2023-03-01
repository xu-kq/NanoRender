#pragma once
#include <algorithm>
#include <tuple>
#include <vector>

#include <Triangle/triangle.h>
#include <Math/Matrix.h>
#include <Fragment/fragment.h>

enum DrawType { WIREFRAME, NORMAL, BLINNPHONG};

class Rasterizer {
public:
	Rasterizer(int width, int height, unsigned char* fb)
		: frame_buffer(fb), Width(width), Height(height),
		depth_buffer(size_t(Width)*Height, std::numeric_limits<double>::lowest()) {}

	void draw_wireframe(Triangle&);
	void draw_fragment(Triangle&);
	void draw(std::vector<Triangle*>&, DrawType);
	void set_model_matrix(const Matrix4d&);
	void set_view_matrix(const Matrix4d&);
	void set_projection_matrix(const Matrix4d&);
	void set_mv_inv_transpose();
	void flush();


private:
	const int Height = 700,
		Width = 700;
	unsigned char* frame_buffer;
	std::vector<double> depth_buffer;

	Matrix4d m;
	Matrix4d v;
	Matrix4d p;
	Matrix4d mv_inv_t;

	// Breseham Algorithm
	void plot_line(const Vector2i& start, const Vector2i& end, const Vector3d& color = Vector3d(255, 255, 255));
	void plot_line(const double x1, const double y1, const double x2, const double y2, 
		const Vector3d& color = Vector3d(255, 255, 255));

	// utility function
	void set_pixel(const int, const int, const Vector3d&);
	void set_pixel(const Vector2i&, const Vector3d&);
};