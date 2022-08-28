// bresenham algorithm

#include<iostream>
#include<array>
#include<Vector.hpp>
#include <lodepng.h>

const int Width = 500;
const int Height = 500;
std::vector<unsigned char> frame_buffer(Width* Height * 4);


void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}
void set_pixel(Vector2i& v, Vector3f& color) {
	int x = v.x(), y = Height - 1 - v.y();
	frame_buffer[4 * Width * y + 4 * x + 0] = color.x();
	frame_buffer[4 * Width * y + 4 * x + 1] = color.y();
	frame_buffer[4 * Width * y + 4 * x + 2] = color.z();
	frame_buffer[4 * Width * y + 4 * x + 3] = 255;
}
void set_pixel(int x, int y, Vector3f& color) {
	set_pixel(Vector2i(x, y), color);
}


void plot_line(const Vector2i& start, const Vector2i& end, Vector3f& color = Vector3f(255, 255, 255)) {
	int sx = start.x(), sy = start.y(),
		ex = end.x(), ey = end.y();
	int dx = ex - sx,
		dy = ey - sy;


	if (dx * dy >= 0) {
		if (dx < 0) {
			std::swap(sx, ex);
			dx = -dx;
		} 
		if (dy < 0){
			std::swap(sy, ey);
			dy = -dy;
		}
		int dx2 = dx * 2,
			dy2 = dy * 2;
		if (dx >= dy) {			// 1
			int check = dy2 - dx;
			while (sx < ex) {
				set_pixel(sx, sy, color);
				if (check < 0) {
					check += dy2;
				}
				else {
					check += dy2 - dx2;
					++sy;
				}
				++sx;
			}
		}
		if (dy > dx) {			// 2
			int check = dy - dx2;
			while (sy < ey) {
				set_pixel(sx, sy, color);
				if (check > 0) {
					check -= dx2;
				}
				else {
					check += dy2 - dx2;
					++sx;
				}
				++sy;
			}
		}
	}
	else {
		if (dx < 0) {
			std::swap(sx, ex);
			std::swap(sy, ey);
			dx = -dx;
			dy = -dy;
		}
		int dx2 = dx * 2,
			dy2 = dy * 2;
		if (dx >= -dy) {		// 8
			int check = dy2 + dx;
			while (sx < ex) {
				set_pixel(sx, sy, color);
				if (check >= 0) {
					check += dy2;
				}
				else {
					check += dy2 + dx2;
					--sy;
				}
				++sx;
			}
		}
		else {					// 7
			int check = dx2 + dy;
			while (sy > ey) {
				set_pixel(sx, sy, color);
				if (check < 0) {
					check += dx2;
				}
				else {
					check += dy2 + dx2;
					++sx;
				}
				--sy;
			}
		}
	}
	set_pixel(sx, sy, color);
}

void plot_line(float x1, float y1, float x2, float y2) {
	plot_line(Vector2i(x1, y1), Vector2i(x2, y2));
}
void flush() {
	frame_buffer.swap(std::vector<unsigned char>(4 * Width * Height));
}

int main() {
	// 1
	char* filename = "../../../image/1.png";
	flush();
	plot_line(Vector2i(0, 0), Vector2i(499, 250));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 2
	filename = "../../../image/2.png";
	flush();
	plot_line(Vector2i(0, 0), Vector2i(250, 499));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 3
	filename = "../../../image/3.png";
	flush();
	plot_line(Vector2i(0, 499), Vector2i(499, 250));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 4
	filename = "../../../image/4.png";
	flush();
	plot_line(Vector2i(0, 499), Vector2i(250, 0));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 5
	filename = "../../../image/5.png";
	flush();
	plot_line(Vector2i(499, 499), Vector2i(0, 250));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 6
	filename = "../../../image/6.png";
	flush();
	plot_line(Vector2i(499, 499), Vector2i(250, 0));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 7
	filename = "../../../image/7.png";
	flush();
	plot_line(Vector2i(0, 499), Vector2i(250, 0));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 8
	filename = "../../../image/8.png";
	flush();
	plot_line(Vector2i(0, 499), Vector2i(499, 250));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 9
	filename = "../../../image/9.png";
	flush();
	plot_line(Vector2i(0, 0), Vector2i(499, 0));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 10
	filename = "../../../image/10.png";
	flush();
	plot_line(Vector2i(499, 0), Vector2i(499, 499));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 11
	filename = "../../../image/11.png";
	flush();
	plot_line(Vector2i(499, 499), Vector2i(0, 499));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 12
	filename = "../../../image/12.png";
	flush();
	plot_line(Vector2i(0, 499), Vector2i(0, 0));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 13
	filename = "../../../image/13.png";
	flush();
	plot_line(Vector2i(0, 0), Vector2i(0, 499));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 14
	filename = "../../../image/14.png";
	flush();
	plot_line(Vector2i(0, 499), Vector2i(499, 499));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 15
	filename = "../../../image/15.png";
	flush();
	plot_line(Vector2i(499, 499), Vector2i(499, 0));
	encodeOneStep(filename, frame_buffer, Width, Height);

	// 16
	filename = "../../../image/16.png";
	flush();
	plot_line(Vector2i(499, 0), Vector2i(0, 0));
	encodeOneStep(filename, frame_buffer, Width, Height);
	return 0;
}