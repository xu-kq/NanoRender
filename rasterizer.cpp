#include"rasterizer.hpp"

void Rasterizer::set_pixel(const Vector2i& v, const Vector3f& color) {
	int x = v.x(), y = Height - 1 - v.y();
	frame_buffer[4 * Width * y + 4 * x + 0] = color.x();
	frame_buffer[4 * Width * y + 4 * x + 1] = color.y();
	frame_buffer[4 * Width * y + 4 * x + 2] = color.z();
	frame_buffer[4 * Width * y + 4 * x + 3] = 255;
}
void Rasterizer::set_pixel(int x, int y, const Vector3f& color) {
	set_pixel(Vector2i(x, y), color);
}


void Rasterizer::plot_line(const Vector2i& start, const Vector2i& end, const Vector3f& color) {
	int sx = start.x(), sy = start.y(),
		ex = end.x(), ey = end.y();
	int dx = ex - sx,
		dy = ey - sy;


	if (dx * dy >= 0) {
		if (dx < 0) {
			std::swap(sx, ex);
			dx = -dx;
		}
		if (dy < 0) {
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

void Rasterizer::plot_line(float x1, float y1, float x2, float y2) {
	plot_line(Vector2i(x1, y1), Vector2i(x2, y2));
}
void Rasterizer::flush() {
	frame_buffer.swap(std::vector<unsigned char>(4 * Width * Height));
}

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void Rasterizer::show() {
	encodeOneStep(Filename, frame_buffer, Width, Height);
}