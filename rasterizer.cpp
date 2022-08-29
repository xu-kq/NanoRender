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

void Rasterizer::plot_line(const Vector2i& start, const Vector2i& end, 
	const Vector3f& color) {
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

void Rasterizer::plot_line(float x1, float y1, float x2, float y2, 
	const Vector3f& color) {
	plot_line(Vector2i(x1, y1), Vector2i(x2, y2), color);
}

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, 
	unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void Rasterizer::show() {
	encodeOneStep(Filename, frame_buffer, Width, Height);
}

void Rasterizer::flush() {
	frame_buffer.swap(std::vector<unsigned char>(4 * Width * Height));
}

void Rasterizer::set_model_matrix(const Matrix4f& model) {
	m = model;
}

void Rasterizer::set_view_matrix(const Matrix4f& view) {
	v = view;
}

void Rasterizer::set_projection_matrix(const Matrix4f& projection) {
	p = projection;
}

void Rasterizer::plot_triangle_wireframe(Triangle& t) {
	Matrix4f mvp = p * v * m;
	Vector4f v0, v1, v2;
	v0 = mvp * to_vec4(t.v0());
	v1 = mvp * to_vec4(t.v1());
	v2 = mvp * to_vec4(t.v2());
	
	v0 = v0 / v0.w();
	v1 = v1 / v1.w();
	v2 = v2 / v2.w();

	// [1,1]^3 -> [0.5, Width - 0.5] x [0.5, Height - 0.5]
	Matrix4f viewport;
	viewport <<
		(Width - 1) / 2, 0, 0, (Width) / 2,
		0, (Height - 1) / 2, 0, (Height) / 2,
		0, 0, 1, 0,
		0, 0, 0, 1;
	v0 = viewport * v0;
	v1 = viewport * v1;
	v2 = viewport * v2;

	Vector2i vert0(v0.x(), v0.y());
	Vector2i vert1(v1.x(), v1.y());
	Vector2i vert2(v2.x(), v2.y());

	plot_line(vert0, vert1);
	plot_line(vert1, vert2);
	plot_line(vert2, vert0);
}

void Rasterizer::rasterize(Triangle& t) {
	plot_triangle_wireframe(t);
}