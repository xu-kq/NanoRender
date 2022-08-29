#include<Vector.hpp>
#include"rasterizer.hpp"
#include"triangle.hpp"
#include"global.hpp"

Matrix4f get_model_matrix(Vector3f offset, float scale = 1.f) {
	float x_offset, y_offset, z_offset;
	x_offset = offset.x(),
		y_offset = offset.y(),
		z_offset = offset.z();

	Matrix4f m;
	m << 
		scale, 0, 0, x_offset,
		0, scale, 0, y_offset,
		0, 0, scale, z_offset,
		0, 0, 0, 1;
	return m;
}
/*
	view_pos:	location of camera
	t:			up direction
	g:			gaze direction
*/
Matrix4f get_view_matrix(const Vector3f view_pos, const Vector3f& t, const Vector3f& g) {
	Vector3f gxt = g.cross(t);
	Matrix4f v, rotation(Matrix4f::Identity()), translation(Matrix4f::Identity());
	
	translation[0][3] = -view_pos.x();
	translation[1][3] = -view_pos.y();
	translation[2][3] = -view_pos.z();
	//rotation << 
	//	gxt.x(), gxt.y(), -gxt.z(), 0,
	//	g.x(), g.y(), -g.z(), 0,
	//	t.x(), t.y(), -t.z(), 0,
	//	0, 0, 0, 1;
	v = rotation * translation;
	
	return v;
}
Matrix4f get_projection_matrix(float fov, float aspect_ratio, float zNear, float zFar) {
	fov = fov / 180 * MY_PI;
	float t, d, l, r, n, f;

	n = zNear;
	f = zFar;
	d = std::tan(fov / 2) * n;
	t = -d;
	r = aspect_ratio * t;
	l = -r;

	Matrix4f v, orthographic, projection;
	projection <<
		n, 0, 0, 0,
		0, n, 0, 0,
		0, 0, n + f, -n* f,
		0, 0, 1, 0;
	orthographic <<
		2.f / (r - l), 0, 0, (r + l) / (r - l),
		0, 2.f / (t - d), 0, (t + d) / (t - d),
		0, 0, 2.f / (n - f), (n + f) / (n - f),
		0, 0, 0, 1;
	v = orthographic * projection;
	return v;
}

int main() {
	const char* filename = "../../../image/output.png";
	Rasterizer r(filename, 700, 700);

//	place model, camera
	//Vector3f offset(0, 0, 0);

	//Vector3f view_pos(5, 5, -5);
	//Vector3f up_dir(0, 0, -1);
	//Vector3f gaze(-sqrt(2) /2, -sqrt(2)/2, 0);

	//float fov, aspect_ratio, zNear, zFar;
	//fov = 90,
	//	aspect_ratio = 1,
	//	zNear = 0.1,
	//	zFar = 10;

	Vector3f offset(0, 0, 0);

	Vector3f view_pos(0, 0, 5);
	Vector3f up_dir(0, 1, 0);
	Vector3f gaze(0, 0, -1);

	float fov, aspect_ratio, zNear, zFar;
	fov = 45,
		aspect_ratio = 1,
		zNear = -0.1,
		zFar = -50;

// load triangles
	float vert[][3] = {	
		{2, 0, -2},
		{0, 2, -2},
		{-2, 0, -2}, 
	};

	int indices[][3] = {
		{0, 1, 2},
	};

	std::vector<Triangle*> t_list;
	Triangle* t = nullptr;
	for (auto& indice : indices) {
		t = new Triangle(vert[indice[0]], vert[indice[1]], vert[indice[2]]);
		t_list.emplace_back(t);
	}

	r.set_model_matrix(get_model_matrix(offset));
	r.set_view_matrix(get_view_matrix(view_pos, up_dir, gaze));
	r.set_projection_matrix(get_projection_matrix(fov, aspect_ratio, zNear, zFar));

	r.rasterize(*t_list[0]);
	r.show();
	return 0;
}