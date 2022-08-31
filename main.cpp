#include<Vector.hpp>
#include"rasterizer.hpp"
#include"triangle.hpp"
#include"global.hpp"
#include"screen.hpp"
#include"lodepng.h"
#include"objLoader.hpp"

Matrix4f get_model_matrix(Vector3f offset, float angle, float scale = 1.f) {
	Matrix4f rotation;
	angle = angle * MY_PI / 180.f;
	//rotation << cos(angle), -sin(angle), 0, 0,
	//	sin(angle), cos(angle), 0, 0,
	//	0, 0, 1, 0,
	//	0, 0, 0, 1;
	rotation << cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1;

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
	return rotation * m;
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

int main(void)
{
	// plot on screen
	int Height = 700, Width = 700;
	Screen screen;

	TCHAR* title = _T("Mini3d (software render tutorial) - ")
		_T("Left/Right: rotation, Up/Down: forward/backward, Space: switch state");

	if (screen.screen_init(Width, Height, title))
			return -1;

	Rasterizer r(Width, Height, screen.get_frame_buffer());

	Vector3f offset(0, 0, 0);
	Vector3f view_pos(0, 0, 10);
	Vector3f up_dir(0, 1, 0);
	Vector3f gaze(0, 0, -1);

	float fov, aspect_ratio, zNear, zFar;
	fov = 45,
		aspect_ratio = 1,
		zNear = -.1f,
		zFar = -50;
	std::string obj_filename("../../../models/spot/spot_triangulated_good.obj");

// load triangles
	objLoader obj(obj_filename);

	std::vector<Triangle*> Tri_lists;
	Triangle* t;
	for (auto& indice : obj.position_ind) {
		Vertex v0(obj.vertex_position[indice[0]]);
		Vertex v1(obj.vertex_position[indice[1]]);
		Vertex v2(obj.vertex_position[indice[2]]);
		t = new Triangle(v0, v1, v2);
		Tri_lists.emplace_back(t);
	}

	int indicator = 0;
	int kbhit = 0;
	float alpha = 0.f;
	while (screen.screen_exit == 0 && screen.screen_keys[VK_ESCAPE] == 0) {
		screen.screen_dispatch();
		r.flush();
		r.set_model_matrix(get_model_matrix(offset, alpha, 1));
		r.set_view_matrix(get_view_matrix(view_pos, up_dir, gaze));
		r.set_projection_matrix(get_projection_matrix(fov, aspect_ratio, zNear, zFar));
		r.draw(Tri_lists,DrawType::WIREFRAME);

		if (screen.screen_keys[VK_UP] && view_pos.z() > -1e2) view_pos.z() -= .05f;
		if (screen.screen_keys[VK_DOWN] && view_pos.z() < 1e2) view_pos.z() += .05f;
		if (screen.screen_keys[VK_LEFT]) alpha += 0.5f;
		if (screen.screen_keys[VK_RIGHT]) alpha -= 0.5f;

		if (screen.screen_keys[VK_SPACE]) {
			if (kbhit == 0) {
				kbhit = 1;
				if (++indicator >= 3) indicator = 0;
				//device.render_state = states[indicator];
		}
	}
		else {
			kbhit = 0;
		}
		screen.screen_update();
		Sleep(1);
	}


	const char* filename = "../../../image/output.png";
	std::vector<unsigned char> image(screen.get_frame_buffer(),
		screen.get_frame_buffer() + sizeof(unsigned char) * 4 * Height * Width);
	for (int j = 0; j < Height; ++j) {
		for (int i = 0; i < Width; ++i) {
			std::swap(image[4 * Width * j + 4 * i + 0], image[4 * Width * j + 4 * i + 2]);
		}
	}
	//Encode the image
	unsigned error = lodepng::encode(filename, image, Width, Height);

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	return 0;
}