#include"global.hpp"
#include<Vector.hpp>

int main()
{
	// -----------------------------  screen init
	int Height = 700, Width = 700;
	Screen screen;
	TCHAR* title = _T("NanoRender (software render tutorial) - ")
		_T("Left/Right: rotation, Up/Down: forward/backward, Space: switch state");
	if (screen.screen_init(Width, Height, title))
			return -1;


	// -----------------------------  rasterizer init
	Rasterizer r(Width, Height, screen.get_frame_buffer());
	// place camera
	Vector3f offset(0, 0, 0);
	Vector3f view_pos(0, 0, 10);
	Vector3f up_dir(0, 1, 0);
	Vector3f gaze(0, 0, -1);
	// perspective properties
	float fov, aspect_ratio, zNear, zFar;
	fov = 45,
		aspect_ratio = 1,
		zNear = -.1f,
		zFar = -50.f;


	// -----------------------------  load "*.obj" file
	std::string obj_filename("../../../models/spot/spot_triangulated_good.obj");
	objLoader obj(obj_filename);
	std::vector<Triangle*> Tri_lists;
	Triangle* t;
	for (size_t i = 0; i < obj.position_ind.size(); ++i) {
		std::vector<int> pos_ind = obj.position_ind[i];
		std::vector<int> tex_ind = obj.texture_ind[i];
		std::vector<int> nor_ind = obj.normal_ind[i];
		std::vector<Vertex> tri_vertex;
		for (int j = 0; j < 3; ++j) {
			Vertex vert(obj.vertex_position.at(pos_ind[j]),
				obj.vertex_texture.at(tex_ind[j]),
				obj.vertex_normal.at(nor_ind[j]));
			tri_vertex.emplace_back(vert);
		}
		t = new Triangle(tri_vertex);
		Tri_lists.emplace_back(t);
	}


	// -----------------------------	update the frame_buffer displayed on the screen
	int indicator = 0;
	int kbhit = 0;
	float alpha = 140.f;
	while (screen.screen_exit == 0 && screen.screen_keys[VK_ESCAPE] == 0) {
		screen.screen_dispatch();
		r.flush();
		r.set_model_matrix(Vertex_process::get_model_matrix(offset, alpha, 2.5f));
		r.set_view_matrix(Vertex_process::get_view_matrix(view_pos, up_dir, gaze));
		r.set_projection_matrix(Vertex_process::get_projection_matrix(fov, aspect_ratio, zNear, zFar));
		r.draw(Tri_lists, DrawType::NORMAL);

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