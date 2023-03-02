#pragma once
#include <algorithm>
#include <tuple>
#include <vector>

#include <Triangle/triangle.h>
#include <Math/Matrix.h>
#include <Fragment/fragment.h>
#include <Texture/texture.h>

enum class DrawType { WIREFRAME, NORMAL, BLINNPHONG, TEXTURE };

class Rasterizer {
private:
	// Ctor.
	Rasterizer() : frame_buffer{nullptr}, depth_buffer{} {}
	Rasterizer(int width, int height, unsigned char *fb)
			: frame_buffer(fb), Width(width), Height(height),
			  depth_buffer(size_t(Width) * Height, std::numeric_limits<double>::lowest()) {}
public:
	// global instance
	static Rasterizer &Instance() {
		static Rasterizer r;
		return r;
	}
	Rasterizer &setting(int width, int height, unsigned char *fb) {
		frame_buffer = fb;
		depth_buffer.resize(Width * Height, std::numeric_limits<double>::lowest());
		return *this;
	}

	void draw(std::vector<std::shared_ptr<Triangle>>& , DrawType);

	void setTexture(std::shared_ptr<Texture> p) { pTexture = p; }
	void set_NANO_MATRIX_M(const Matrix4d &);
	void set_NANO_MATRIX_V(const Matrix4d &);
	void set_NANO_MATRIX_P(const Matrix4d &);
	void set_NANO_MATRIX_IT_MV();
	void flush();

private:
	int Height = 700;
	int Width = 700;
	unsigned char *frame_buffer;
	std::vector<double> depth_buffer;
	std::shared_ptr<Texture> pTexture;

	Matrix4d NANO_MATRIX_M;
	Matrix4d NANO_MATRIX_V;
	Matrix4d NANO_MATRIX_P;
	Matrix4d NANO_MATRIX_IT_MV;

	// Breseham Algorithm
	void plot_line(const Vector2i &start, const Vector2i &end, const Vector3d &color = Vector3d(255, 255, 255));
	void plot_line(double x1, double y1, double x2, double y2,
	               const Vector3d &color = Vector3d(255, 255, 255));

	// utility function
	void set_pixel(int, int, const Vector3d &);
	void set_pixel(const Vector2i &, const Vector3d &);
	void drawWireFrame(Triangle &);
	void drawNormal(Triangle &);
	void drawFragment(Triangle &);
	void drawTexture(Triangle &t);
};