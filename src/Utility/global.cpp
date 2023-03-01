#include <Utility/global.h>

namespace Vertex_process {
Matrix4d get_model_matrix(const Vector3d& offset, const double _angle, const double scale_factor = 1.) {
	Matrix4d rotation;
	double angle = _angle * MY_PI / 180.f;
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

	double x_offset, y_offset, z_offset;
	x_offset = offset.x(),
		y_offset = offset.y(),
		z_offset = offset.z();

	Matrix4d scale;
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
Matrix4d get_view_matrix(const Vector3d& view_pos, const Vector3d& t, const Vector3d& g) {
	Vector3d gxt = g.cross(t);
	Matrix4d v, rotation = Matrix4d::Identity(), translation = Matrix4d::Identity();

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

Matrix4d get_projection_matrix(const double _fov, const double _aspect_ratio,
                               const double _zNear, const double _zFar) {
	double fov = _fov / 180 * MY_PI;
	double t, d, l, r, n, f;

	n = _zNear;
	f = _zFar;
	d = std::tan(fov / 2) * n;
	t = -d;
	r = _aspect_ratio * t;
	l = -r;

	Matrix4d v, orthographic, projection;
	projection <<
		n, 0, 0, 0,
		0, n, 0, 0,
		0, 0, n + f, -n * f,
		0, 0, 1, 0;
	orthographic <<
		2. / (r - l), 0, 0, - (r + l) / (r - l),
		0, 2. / (t - d), 0, - (t + d) / (t - d),
		0, 0, 2. / (n - f), - (n + f) / (n - f),
		0, 0, 0, 1;
	v = orthographic * projection;
	return v;
}
}