#include"rasterizer.hpp"

void Rasterizer::set_pixel(const Vector2i& v, const Vector3f& color) {
	int x = v.x(), y = Height - 1 - v.y();
	if (x < 0 || x >= Width || y < 0 || y >= Height) {
		return;
	}
	frame_buffer[4 * Width * y + 4 * x + 0] = (unsigned char)color.z();
	frame_buffer[4 * Width * y + 4 * x + 1] = (unsigned char)color.y();
	frame_buffer[4 * Width * y + 4 * x + 2] = (unsigned char)color.x();
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
	plot_line(Vector2i(int(x1), int(y1)), Vector2i(int(x2), int(y2)), color);
}

void Rasterizer::flush() {
	memset(frame_buffer, 0, sizeof(unsigned char) * 4 * Width * Height);
	std::fill(depth_buffer.begin(), depth_buffer.end(), std::numeric_limits<float>::lowest());
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

void Rasterizer::draw_wireframe(Triangle& t) {
	Matrix4f mvp = p * v * m;
	Vector4f v0, v1, v2;
	v0 = mvp * to_vec4(t.v0.pos);
	v1 = mvp * to_vec4(t.v1.pos);
	v2 = mvp * to_vec4(t.v2.pos);
	
	v0 = v0 / v0.w();
	v1 = v1 / v1.w();
	v2 = v2 / v2.w();

	// [1,1]^3 -> [0.5, Width - 0.5] x [0.5, Height - 0.5]
	Matrix4f viewport;
	viewport <<
		0.5f * Width, 0, 0, 0.5f * (Width),
		0, 0.5f * (Height), 0, 0.5f * (Height),
		0, 0, 1.f, 0,
		0, 0, 0, 1.f;
	v0 = viewport * v0;
	v1 = viewport * v1;
	v2 = viewport * v2;

	Vector2i vert0(int(v0.x()), int(v0.y()));
	Vector2i vert1(int(v1.x()), int(v1.y()));
	Vector2i vert2(int(v2.x()), int(v2.y()));

	plot_line(vert0, vert1);
	plot_line(vert1, vert2);
	plot_line(vert2, vert0);
}

bool insideTriangle(Vector3f v0, Vector3f v1, Vector3f v2, Vector3f p){ 
	Vector3f f0, f1, f2;
	f0 = v0.cross(v1);
	f1 = v1.cross(v2);
	f2 = v2.cross(v0);

	if (p.dot(f0) * v2.dot(f0) >= 0 && p.dot(f1) * v0.dot(f1) >= 0 && p.dot(f2) * v1.dot(f2) >= 0) {
		return true;
	}
	return false;
}
Vector3f computeBaryCentric2D(Vector3f v0, Vector3f v1, Vector3f v2, Vector3f p) {
	float alpha, beta, gamma;
	alpha = (p.x() * (v1.y() - v2.y()) + (v2.x() - v1.x()) * p.y() + v1.x() * v2.y() - v2.x() * v1.y()) / (v0.x() * (v1.y() - v2.y()) + (v2.x() - v1.x()) * v0.y() + v1.x() * v2.y() - v2.x() * v1.y());
	beta = (p.x() * (v2.y() - v0.y()) + (v0.x() - v2.x()) * p.y() + v2.x() * v0.y() - v0.x() * v2.y()) / (v1.x() * (v2.y() - v0.y()) + (v0.x() - v2.x()) * v1.y() + v2.x() * v0.y() - v0.x() * v2.y());
	gamma = (p.x() * (v0.y() - v1.y()) + (v1.x() - v0.x()) * p.y() + v0.x() * v1.y() - v1.x() * v0.y()) / (v2.x() * (v0.y() - v1.y()) + (v1.x() - v0.x()) * v2.y() + v0.x() * v1.y() - v1.x() * v0.y());
	return { alpha, beta, gamma };
}

void Rasterizer::draw_fragment(Triangle& t) {
	Matrix4f mvp = p * v * m;
	Vector4f v0, v1, v2;
	v0 = mvp * to_vec4(t.v0.pos);
	v1 = mvp * to_vec4(t.v1.pos);
	v2 = mvp * to_vec4(t.v2.pos);

	v0 = v0 / v0.w();
	v1 = v1 / v1.w();
	v2 = v2 / v2.w();

	// [1,1]^3 -> [0.5, Width - 0.5] x [0.5, Height - 0.5]
	Matrix4f viewport;
	viewport <<
		0.5f * Width, 0, 0, 0.5f * (Width),
		0, 0.5f * (Height), 0, 0.5f * (Height),
		0, 0, 1.f, 0,
		0, 0, 0, 1.f;
	v0 = viewport * v0;
	v1 = viewport * v1;
	v2 = viewport * v2;

	float xmin, xmax, ymin, ymax;
	xmin = std::min({ v0.x(), v1.x(), v2.x() });
	xmax = std::max({ v0.x(), v1.x(), v2.x() });
	ymin = std::min({ v0.y(), v1.y(), v2.y() });
	ymax = std::max({ v0.y(), v1.y(), v2.y() });

	int xlow, xupp, ylow, yupp;
	xlow = std::max(int(round(xmin)), 0);
	xupp = std::min(int(round(xmax)), Width);
	ylow = std::max(int(round(ymin)), 0);
	yupp = std::min(int(round(ymax)), Height);

	for (int j = ylow; j < yupp; ++j) {
		for (int i = xlow; i < xupp; ++i) {
			if (insideTriangle(Vector3f(v0.x(), v0.y(), 1), Vector3f(v1.x(), v1.y(), 1),
				Vector3f(v2.x(), v2.y(), 1), Vector3f(0.5f + i, 0.5f + j, 1))) {
				Vector3f coef;
				coef = computeBaryCentric2D(Vector3f(v0.x(), v0.y(), 1), Vector3f(v1.x(), v1.y(), 1),
					Vector3f(v2.x(), v2.y(), 1), Vector3f(0.5f + i, 0.5f + j, 1));
				float z_interpolate = coef.x() * v0.z() + coef.y() * v1.z() + coef.z() * v2.z();
				Vector3f color = t.v0.col.cwsiseDot(coef.x()) + t.v1.col.cwsiseDot(coef.y()) + t.v2.col.cwsiseDot(coef.z());
				if (z_interpolate > depth_buffer[Width * j + i]) {
					depth_buffer[Width * j + i] = z_interpolate;
					set_pixel({ i, j }, color);
				}
			}
		}
	}


}

void Rasterizer::draw(std::vector<Triangle*> Tri_lists, DrawType type = DrawType::WIREFRAME) {
	switch (type) {
	case DrawType::WIREFRAME:
		for (auto tri : Tri_lists) {
			draw_wireframe(*tri);
		}
		break;
	case DrawType::FRAGMENT:
		for (auto tri : Tri_lists) {
			draw_fragment(*tri);
		}
		break;
	}
}
