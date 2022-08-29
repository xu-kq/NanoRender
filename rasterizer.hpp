#pragma once
#include<lodepng.h>
#include<Vector.hpp>
#include<vector>

class Rasterizer {
public:
	Rasterizer(int width, int height)
		: Width(width), Height(height), frame_buffer(4 * width * height) { }
	Rasterizer(const char* filename, int width, int height)
		: Filename(new char[strlen(filename) + 1]),
		Width(width), Height(height), frame_buffer(4 * width * height) {
		memcpy(Filename, filename, strlen(filename) + 1);
	}
	// Breseham Algorithm
	void plot_line(const Vector2i& start, const Vector2i& end, const Vector3f& color = Vector3f(255, 255, 255));
	void plot_line(float x1, float y1, float x2, float y2);
	void show();
private:
	char* Filename = "../../../image/output.png";
	const int Height = 700,
		Width = 700;
	std::vector<unsigned char> frame_buffer;

	// utility function
	void set_pixel(int, int, const Vector3f&);
	void set_pixel(const Vector2i&, const Vector3f&);
	void flush();
};