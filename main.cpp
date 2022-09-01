#include"global.hpp"
#include<Vector.hpp>


Matrix4f get_model_matrix(const Vector3f& offset, const float _angle, const float scale = 1.f) {
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
	v = rotation * translation;

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
	// -----------------------------  screen init
	int Height = 700, Width = 700;
	Screen screen;
	TCHAR* title = _T("Mini3d (software render tutorial) - ")
		_T("Left/Right: rotation, Up/Down: forward/backward, Space: switch state");
	if (screen.screen_init(Width, Height, title))
			return -1;


	// -----------------------------  rasterizer init
	Rasterizer r(Width, Height, screen.get_frame_buffer());
	// place camera
	Vector3f offset(0, 0, 0);
	Vector3f view_pos(0, 0, 5);
	Vector3f up_dir(0, 1, 0);
	Vector3f gaze(0, 0, -1);
	// perspective properties
	float fov, aspect_ratio, zNear, zFar;
	fov = 45,
		aspect_ratio = 1,
		zNear = -.1f,
		zFar = -50;


	// -----------------------------  load "*.obj" file
	std::string obj_filename("../../../models/spot/spot_triangulated_good.obj");
	objLoader obj(obj_filename);
	std::vector<Triangle*> Tri_lists;
	Triangle* t;
	for (auto& indice : obj.position_ind) {
		size_t pos_ind, tex_ind, nor_ind;
		pos_ind = indice[0];
		tex_ind = indice[1];
		nor_ind = indice[2];

		t = new Triangle(obj.vertex_position[pos_ind], 
			obj.vertex_position[tex_ind], 
			obj.vertex_position[nor_ind]
		);
		Tri_lists.emplace_back(t);
	}


	// -----------------------------	update the frame_buffer displayed on the screen
	int indicator = 0;
	int kbhit = 0;
	float alpha = 0.f;
	while (screen.screen_exit == 0 && screen.screen_keys[VK_ESCAPE] == 0) {
		screen.screen_dispatch();
		r.flush();
		r.set_model_matrix(get_model_matrix(offset, alpha, 1));
		r.set_view_matrix(get_view_matrix(view_pos, up_dir, gaze));
		r.set_projection_matrix(get_projection_matrix(fov, aspect_ratio, zNear, zFar));
		r.draw(Tri_lists, DrawType::WIREFRAME);

		if (screen.screen_keys[VK_UP]) view_pos.z() -= .05f;
		if (screen.screen_keys[VK_DOWN]) view_pos.z() += .05f;
		if (screen.screen_keys[VK_LEFT]) alpha += .5f;
		if (screen.screen_keys[VK_RIGHT]) alpha -= .5f;

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

	// -----------------------------	save the last frame to the "output.png" file
	const char* filename = "../../../image/output.png";
	std::vector<unsigned char> image(screen.get_frame_buffer(),
		screen.get_frame_buffer() + sizeof(unsigned char) * 4 * Height * Width);
	for (size_t j = 0; j < Height; ++j) {
		for (size_t i = 0; i < Width; ++i) {
			std::swap(image[j * 4 * Width + i * 4 + 0], image[j * 4 * Width + i * 4 + 2]);
		}
	}
	// Encode the image
	unsigned error = lodepng::encode(filename, image, Width, Height);
	// if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	return 0;
}