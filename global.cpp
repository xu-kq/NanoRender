#include"global.hpp"

namespace Vertex_process {
Matrix4f get_model_matrix(const Vector3f& offset, const float _angle, const float scale_factor = 1.f) {
	Matrix4f rotation;
	float angle = _angle * MY_PI / 180.f;
	//rotation << 
	// cos(angle), -sin(angle), 0, 0,
	//	sin(angle), cos(angle), 0, 0,
	//	0, 0, 1, 0,
	//	0, 0, 0, 1;
	rotation <<
		cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1;

	float x_offset, y_offset, z_offset;
	x_offset = offset.x(),
		y_offset = offset.y(),
		z_offset = offset.z();

	Matrix4f scale;
	scale <<
		scale_factor, 0, 0, 0,
		0, scale_factor, 0, 0,
		0, 0, scale_factor, 0,
		0, 0, 0, 1;
	return rotation * scale;
}

/*
	view_pos:	location of camera
	t:			up direction
	g:			gaze direction
*/
Matrix4f get_view_matrix(const Vector3f& view_pos, const Vector3f& t, const Vector3f& g) {
	Vector3f gxt = g.cross(t);
	Matrix4f v, rotation(Matrix4f::Identity()), translation(Matrix4f::Identity());

	translation[0][3] = -view_pos.x();
	translation[1][3] = -view_pos.y();
	translation[2][3] = -view_pos.z();
	rotation <<
		gxt.x(), gxt.y(), -gxt.z(), 0,
		t.x(), t.y(), -t.z(), 0,
		g.x(), g.y(), -g.z(), 0,
		0, 0, 0, 1;
	v =  translation * rotation;

	return v;
}

Matrix4f get_projection_matrix(const float _fov, const float _aspect_ratio,
	const float _zNear, const float _zFar) {
	float fov = _fov / 180 * MY_PI;
	float t, d, l, r, n, f;

	n = _zNear;
	f = _zFar;
	d = std::tan(fov / 2) * n;
	t = -d;
	r = _aspect_ratio * t;
	l = -r;

	Matrix4f v, orthographic, projection;
	projection <<
		n, 0, 0, 0,
		0, n, 0, 0,
		0, 0, n + f, -n * f,
		0, 0, 1, 0;
	orthographic <<
		2.f / (r - l), 0, 0, - (r + l) / (r - l),
		0, 2.f / (t - d), 0, - (t + d) / (t - d),
		0, 0, 2.f / (n - f), - (n + f) / (n - f),
		0, 0, 0, 1;
	v = orthographic * projection;
	return v;
}
}