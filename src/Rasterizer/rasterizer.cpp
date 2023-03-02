#include <Rasterizer/rasterizer.h>

void Rasterizer::set_pixel(const Vector2i &v, const Vector3d &color) {
	int x = v.x(), y = Height - 1 - v.y();
	if (x < 0 || x >= Width || y < 0 || y >= Height) {
		return;
	}
	frame_buffer[4 * Width * y + 4 * x + 0] = (unsigned char)color.z();
	frame_buffer[4 * Width * y + 4 * x + 1] = (unsigned char)color.y();
	frame_buffer[4 * Width * y + 4 * x + 2] = (unsigned char)color.x();
	frame_buffer[4 * Width * y + 4 * x + 3] = (unsigned char)255;
}

void Rasterizer::set_pixel(const int x, const int y, const Vector3d &color) {
	set_pixel({x, y}, color);
}

void Rasterizer::plot_line(const Vector2i &start, const Vector2i &end,
                           const Vector3d &color) {
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
		if (dx >= dy) {      // 1
			int check = dy2 - dx;
			while (sx < ex) {
				set_pixel(sx, sy, color);
				if (check < 0) {
					check += dy2;
				} else {
					check += dy2 - dx2;
					++sy;
				}
				++sx;
			}
		}
		if (dy > dx) {      // 2
			int check = dy - dx2;
			while (sy < ey) {
				set_pixel(sx, sy, color);
				if (check > 0) {
					check -= dx2;
				} else {
					check += dy2 - dx2;
					++sx;
				}
				++sy;
			}
		}
	} else {
		if (dx < 0) {
			std::swap(sx, ex);
			std::swap(sy, ey);
			dx = -dx;
			dy = -dy;
		}
		int dx2 = dx * 2,
				dy2 = dy * 2;
		if (dx >= -dy) {    // 8
			int check = dy2 + dx;
			while (sx < ex) {
				set_pixel(sx, sy, color);
				if (check >= 0) {
					check += dy2;
				} else {
					check += dy2 + dx2;
					--sy;
				}
				++sx;
			}
		} else {          // 7
			int check = dx2 + dy;
			while (sy > ey) {
				set_pixel(sx, sy, color);
				if (check < 0) {
					check += dx2;
				} else {
					check += dy2 + dx2;
					++sx;
				}
				--sy;
			}
		}
	}
	set_pixel(sx, sy, color);
}

void Rasterizer::plot_line(const double x1, const double y1, const double x2, const double y2,
                           const Vector3d &color) {
	plot_line({int(x1), int(y1)}, {int(x2), int(y2)}, color);
}

void Rasterizer::flush() {
	memset(frame_buffer, 0, sizeof(unsigned char) * 4 * Width * Height);
	std::fill(depth_buffer.begin(), depth_buffer.end(), std::numeric_limits<double>::lowest());
}

void Rasterizer::set_NANO_MATRIX_M(const Matrix4d &model) {
	NANO_MATRIX_M = model;
}

void Rasterizer::set_NANO_MATRIX_V(const Matrix4d &view) {
	NANO_MATRIX_V = view;
}

void Rasterizer::set_NANO_MATRIX_P(const Matrix4d &projection) {
	NANO_MATRIX_P = projection;
}

void Rasterizer::set_NANO_MATRIX_IT_MV() {
	NANO_MATRIX_IT_MV = (NANO_MATRIX_V * NANO_MATRIX_M).inverse().transpose();
}

void Rasterizer::drawWireFrame(Triangle &t) {
	Matrix4d mvp = NANO_MATRIX_P * NANO_MATRIX_V * NANO_MATRIX_M;
	Vector4f v0, v1, v2;
	v0 = mvp * to_vec4(t.v0.position);
	v1 = mvp * to_vec4(t.v1.position);
	v2 = mvp * to_vec4(t.v2.position);

	v0 = v0 / v0.w();
	v1 = v1 / v1.w();
	v2 = v2 / v2.w();

	// [1,1]^3 -> [0.5, Width - 0.5] x [0.5, Height - 0.5]
	Matrix4d viewport;
	viewport <<
	         0.5 * Width, 0, 0, 0.5 * (Width),
			0, 0.5 * (Height), 0, 0.5 * (Height),
			0, 0, 1., 0,
			0, 0, 0, 1.;
	v0 = viewport * v0;
	v1 = viewport * v1;
	v2 = viewport * v2;

	plot_line({int(v0.x()), int(v0.y())}, {int(v1.x()), int(v1.y())});
	plot_line({int(v1.x()), int(v1.y())}, {int(v2.x()), int(v2.y())});
	plot_line({int(v2.x()), int(v2.y())}, {int(v0.x()), int(v0.y())});
}

bool insideTriangle(Vector3d v0, Vector3d v1, Vector3d v2, Vector3d p) {
	Vector3d f0, f1, f2;
	f0 = v0.cross(v1);
	f1 = v1.cross(v2);
	f2 = v2.cross(v0);

	if (p.dot(f0) * v2.dot(f0) >= 0 && p.dot(f1) * v0.dot(f1) >= 0 && p.dot(f2) * v1.dot(f2) >= 0) {
		return true;
	}
	return false;
}

Vector3d computeBaryCentric2D(Vector3d v0, Vector3d v1, Vector3d v2, Vector3d p) {
	double alpha, beta, gamma;
	alpha = (p.x() * (v1.y() - v2.y()) + (v2.x() - v1.x()) * p.y() + v1.x() * v2.y() - v2.x() * v1.y())
			/ (v0.x() * (v1.y() - v2.y()) + (v2.x() - v1.x()) * v0.y() + v1.x() * v2.y() - v2.x() * v1.y());
	beta = (p.x() * (v2.y() - v0.y()) + (v0.x() - v2.x()) * p.y() + v2.x() * v0.y() - v0.x() * v2.y())
			/ (v1.x() * (v2.y() - v0.y()) + (v0.x() - v2.x()) * v1.y() + v2.x() * v0.y() - v0.x() * v2.y());
	gamma = (p.x() * (v0.y() - v1.y()) + (v1.x() - v0.x()) * p.y() + v0.x() * v1.y() - v1.x() * v0.y())
			/ (v2.x() * (v0.y() - v1.y()) + (v1.x() - v0.x()) * v2.y() + v0.x() * v1.y() - v1.x() * v0.y());
	return {alpha, beta, gamma};
}

void Rasterizer::drawNormal(Triangle &t) {
	Matrix4d mvp = NANO_MATRIX_P * NANO_MATRIX_V * NANO_MATRIX_M;
	Vector4f v0, v1, v2;
	v0 = mvp * to_vec4(t.v0.position);
	v1 = mvp * to_vec4(t.v1.position);
	v2 = mvp * to_vec4(t.v2.position);

	// viewspace n and v
	Vector3d n0, n1, n2;
	n0 = to_vec3(NANO_MATRIX_IT_MV * to_vec4(t.v0.normal));
	n1 = to_vec3(NANO_MATRIX_IT_MV * to_vec4(t.v1.normal));
	n2 = to_vec3(NANO_MATRIX_IT_MV * to_vec4(t.v2.normal));

	Vector3d view_v0, view_v1, view_v2;
	view_v0 = to_vec3(NANO_MATRIX_V * NANO_MATRIX_M * to_vec4(t.v0.position));
	view_v1 = to_vec3(NANO_MATRIX_V * NANO_MATRIX_M * to_vec4(t.v1.position));
	view_v2 = to_vec3(NANO_MATRIX_V * NANO_MATRIX_M * to_vec4(t.v2.position));

	v0 = v0 / v0.w();
	v1 = v1 / v1.w();
	v2 = v2 / v2.w();

	// [1,1]^3 -> [0.5, Width - 0.5] x [0.5, Height - 0.5]
	Matrix4d viewport;
	viewport <<
	         0.5 * Width, 0, 0, 0.5 * (Width),
			0, 0.5 * (Height), 0, 0.5 * (Height),
			0, 0, 1., 0,
			0, 0, 0, 1.;
	v0 = viewport * v0;
	v1 = viewport * v1;
	v2 = viewport * v2;

	double xmin, xmax, ymin, ymax;
	xmin = std::min({v0.x(), v1.x(), v2.x()});
	xmax = std::max({v0.x(), v1.x(), v2.x()});
	ymin = std::min({v0.y(), v1.y(), v2.y()});
	ymax = std::max({v0.y(), v1.y(), v2.y()});

	int xlow, xupp, ylow, yupp;
	xlow = std::max(int(xmin), 0);
	xupp = std::min(int(xmax + 1), Width - 1);
	ylow = std::max(int(ymin), 0);
	yupp = std::min(int(ymax + 1), Height - 1);

	for (size_t j = ylow; j <= yupp; ++j) {
		for (size_t i = xlow; i <= xupp; ++i) {
			if (insideTriangle({v0.x(), v0.y(), 1}, {v1.x(), v1.y(), 1},
			                   {v2.x(), v2.y(), 1}, {0.5 + i, 0.5 + j, 1})) {
				Vector3d coef = computeBaryCentric2D({v0.x(), v0.y(), 1}, {v1.x(), v1.y(), 1},
				                                     {v2.x(), v2.y(), 1}, {0.5 + i, 0.5 + j, 1});
				double z_interpolate = coef.x() * v0.z() + coef.y() * v1.z() + coef.z() * v2.z();
				if (z_interpolate >= depth_buffer[Width * j + i]) {
					depth_buffer[Width * j + i] = z_interpolate;
					Vector3d normal = n0 * coef.x()
							+ n1 * coef.y()
							+ n2 * coef.z();
					Vector3d color = (normal.normalized() + Vector3d(1, 1, 1))/ 2 * 255.f ;
					set_pixel(int(i), int(j), color);
				}
			}
		}
	}
}
void Rasterizer::drawFragment(Triangle &t) {
	Matrix4d mvp = NANO_MATRIX_P * NANO_MATRIX_V * NANO_MATRIX_M;
	Vector4f v0, v1, v2;
	v0 = mvp * to_vec4(t.v0.position);
	v1 = mvp * to_vec4(t.v1.position);
	v2 = mvp * to_vec4(t.v2.position);

	// viewspace n and v
	Vector3d n0, n1, n2;
	n0 = to_vec3(NANO_MATRIX_IT_MV * to_vec4(t.v0.normal));
	n1 = to_vec3(NANO_MATRIX_IT_MV * to_vec4(t.v1.normal));
	n2 = to_vec3(NANO_MATRIX_IT_MV * to_vec4(t.v2.normal));

	Vector3d view_v0, view_v1, view_v2;
	view_v0 = to_vec3(NANO_MATRIX_V * NANO_MATRIX_M * to_vec4(t.v0.position));
	view_v1 = to_vec3(NANO_MATRIX_V * NANO_MATRIX_M * to_vec4(t.v1.position));
	view_v2 = to_vec3(NANO_MATRIX_V * NANO_MATRIX_M * to_vec4(t.v2.position));

	v0 = v0 / v0.w();
	v1 = v1 / v1.w();
	v2 = v2 / v2.w();

	// [1,1]^3 -> [0.5, Width - 0.5] x [0.5, Height - 0.5]
	Matrix4d viewport;
	viewport <<
	         0.5 * Width, 0, 0, 0.5 * (Width),
			0, 0.5 * (Height), 0, 0.5 * (Height),
			0, 0, 1., 0,
			0, 0, 0, 1.;
	v0 = viewport * v0;
	v1 = viewport * v1;
	v2 = viewport * v2;

	double xmin, xmax, ymin, ymax;
	xmin = std::min({v0.x(), v1.x(), v2.x()});
	xmax = std::max({v0.x(), v1.x(), v2.x()});
	ymin = std::min({v0.y(), v1.y(), v2.y()});
	ymax = std::max({v0.y(), v1.y(), v2.y()});

	int xlow, xupp, ylow, yupp;
	xlow = std::max(int(xmin), 0);
	xupp = std::min(int(xmax + 1), Width - 1);
	ylow = std::max(int(ymin), 0);
	yupp = std::min(int(ymax + 1), Height - 1);

	for (size_t j = ylow; j <= yupp; ++j) {
		for (size_t i = xlow; i <= xupp; ++i) {
			if (insideTriangle({v0.x(), v0.y(), 1}, {v1.x(), v1.y(), 1},
			                   {v2.x(), v2.y(), 1}, {0.5 + i, 0.5 + j, 1})) {
				Vector3d coef = computeBaryCentric2D({v0.x(), v0.y(), 1}, {v1.x(), v1.y(), 1},
				                                     {v2.x(), v2.y(), 1}, {0.5 + i, 0.5 + j, 1});
				double z_interpolate = coef.x() * v0.z() + coef.y() * v1.z() + coef.z() * v2.z();
				if (z_interpolate >= depth_buffer[Width * j + i]) {
					depth_buffer[Width * j + i] = z_interpolate;
					Vector3d position = coef.x() * view_v0
							+ coef.y() * view_v1
							+ coef.z() * view_v2;
					Vector3d normal = n0 * coef.x()
							+ n1 * coef.y()
							+ n2 * coef.z();
					Vector3d color = fragment_shader_BlinnPhong(position, normal);
					set_pixel(int(i), int(j), color);
				}
			}
		}
	}
}

void Rasterizer::drawTexture(Triangle &t) {
	Matrix4d mvp = NANO_MATRIX_P * NANO_MATRIX_V * NANO_MATRIX_M;
	Vector4f v0, v1, v2;
	v0 = mvp * to_vec4(t.v0.position);
	v1 = mvp * to_vec4(t.v1.position);
	v2 = mvp * to_vec4(t.v2.position);

	// viewspace n and v
	Vector3d n0, n1, n2;
	n0 = to_vec3(NANO_MATRIX_IT_MV * to_vec4(t.v0.normal));
	n1 = to_vec3(NANO_MATRIX_IT_MV * to_vec4(t.v1.normal));
	n2 = to_vec3(NANO_MATRIX_IT_MV * to_vec4(t.v2.normal));

	Vector3d view_v0, view_v1, view_v2;
	view_v0 = to_vec3(NANO_MATRIX_V * NANO_MATRIX_M * to_vec4(t.v0.position));
	view_v1 = to_vec3(NANO_MATRIX_V * NANO_MATRIX_M * to_vec4(t.v1.position));
	view_v2 = to_vec3(NANO_MATRIX_V * NANO_MATRIX_M * to_vec4(t.v2.position));

	v0 = v0 / v0.w();
	v1 = v1 / v1.w();
	v2 = v2 / v2.w();

	// [1,1]^3 -> [0.5, Width - 0.5] x [0.5, Height - 0.5]
	Matrix4d viewport;
	viewport <<
	         0.5 * Width, 0, 0, 0.5 * (Width),
			0, 0.5 * (Height), 0, 0.5 * (Height),
			0, 0, 1., 0,
			0, 0, 0, 1.;
	v0 = viewport * v0;
	v1 = viewport * v1;
	v2 = viewport * v2;

	double xmin, xmax, ymin, ymax;
	xmin = std::min({v0.x(), v1.x(), v2.x()});
	xmax = std::max({v0.x(), v1.x(), v2.x()});
	ymin = std::min({v0.y(), v1.y(), v2.y()});
	ymax = std::max({v0.y(), v1.y(), v2.y()});

	int xlow, xupp, ylow, yupp;
	xlow = std::max(int(xmin), 0);
	xupp = std::min(int(xmax + 1), Width - 1);
	ylow = std::max(int(ymin), 0);
	yupp = std::min(int(ymax + 1), Height - 1);

	for (size_t j = ylow; j <= yupp; ++j) {
		for (size_t i = xlow; i <= xupp; ++i) {
			if (insideTriangle({v0.x(), v0.y(), 1}, {v1.x(), v1.y(), 1},
			                   {v2.x(), v2.y(), 1}, {0.5 + i, 0.5 + j, 1})) {
				Vector3d coef = computeBaryCentric2D({v0.x(), v0.y(), 1}, {v1.x(), v1.y(), 1},
				                                     {v2.x(), v2.y(), 1}, {0.5 + i, 0.5 + j, 1});
				double z_interpolate = coef.x() * v0.z() + coef.y() * v1.z() + coef.z() * v2.z();
				if (z_interpolate >= depth_buffer[Width * j + i]) {
					depth_buffer[Width * j + i] = z_interpolate;
					Vector3d position = coef.x() * view_v0
							+ coef.y() * view_v1
							+ coef.z() * view_v2;
					Vector3d normal = n0 * coef.x()
							+ n1 * coef.y()
							+ n2 * coef.z();

					Vector2d texture_coords =
							  t.v0.texture * coef.x()
							+ t.v1.texture * coef.y()
							+ t.v2.texture * coef.z();
					auto texture_color = pTexture->getColor(texture_coords);
					texture_color = pTexture->getColor(t.v0.texture);
					Vector3d color = fragment_shader_Texture(position, texture_color , normal);
					set_pixel(int(i), int(j), color);
				}
			}
		}
	}
}

void Rasterizer::draw(std::vector<std::shared_ptr<Triangle>> &Tri_lists, DrawType type = DrawType::WIREFRAME) {
	set_NANO_MATRIX_IT_MV();
	switch (type) {
	case DrawType::WIREFRAME:
		for (auto tri : Tri_lists) {
			drawWireFrame(*tri);
		}
		break;
	case DrawType::NORMAL:
		for (auto tri : Tri_lists) {
			drawNormal(*tri);
		}
		break;
	case DrawType::BLINNPHONG:
		for (auto tri : Tri_lists) {
			drawFragment(*tri);
		}
		break;
	case DrawType::TEXTURE:
		for (auto tri : Tri_lists) {
			drawTexture(*tri);
		}
	}

}
