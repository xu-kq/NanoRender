#include <Utility/global.h>

int main() {
	std::string input_model{"../../models/spot/spot_triangulated_good.obj"};
	std::string output_image{"../../image/output.png"};
	std::string texture_image{"../../models/spot/spot_texture.png"};

	// -----------------------------  screen init
	constexpr int Height = 700, Width = 700;
	auto screen = Screen::Instance().setting(Width, Height);

	// -----------------------------  rasterizer init
	auto r = Rasterizer::Instance().setting(Width, Height, screen.getFrameBuffer());

	// place camera
	Vector3d offset(0, 0, 0);
	Vector3d view_pos(0, 0, 10);
	Vector3d up_dir(0, 1, 0);
	Vector3d gaze(0, 0, -1);
	// perspective properties
	float fov, aspect_ratio, zNear, zFar;
	fov = 45.f;
	aspect_ratio = 1.f;
	zNear = -.1f;
	zFar = -50.f;


	// -----------------------------  load "*.obj" file
	objLoader obj;
	std::string obj_filename(input_model);
	obj.read(obj_filename);
	std::vector<std::shared_ptr<Triangle>> TriLists;
	for (int i = 0; i < obj.indPosition.size(); ++i) {
		auto pos_ind = obj.indPosition[i];
		auto tex_ind = obj.indTexture[i];
		auto nor_ind = obj.indNormal[i];

		std::vector<Vertex> triVertex;
		for (int j = 0; j < 3; ++j) {
			triVertex.emplace_back(obj.vPosition.at(pos_ind[j]),
			                        obj.vTexture.at(tex_ind[j]),
			                        obj.vNormal.at(nor_ind[j]));
		}
		TriLists.emplace_back(std::make_shared<Triangle>(triVertex));
	}

	// Texture
	auto pTexture = std::make_shared<Texture>(texture_image);
	r.setTexture(pTexture);

	// -----------------------------	update the frame_buffer displayed on the screen
	int indicator = 0;
	int kbhit = 0;
	float alpha = 140.f;
	std::unordered_map<int, DrawType> renderState{
			{0, DrawType::WIREFRAME},
			{1, DrawType::NORMAL},
			{2, DrawType::BLINNPHONG},
			{3, DrawType::TEXTURE}
	};
	while (screen.screen_exit == 0 && screen.screen_keys[VK_ESCAPE] == 0) {
		screen.screen_dispatch();
		{
			r.flush();
			r.set_NANO_MATRIX_M(Vertex_process::get_model_matrix(offset, alpha, 2.5f));
			r.set_NANO_MATRIX_V(Vertex_process::get_view_matrix(view_pos, up_dir, gaze));
			r.set_NANO_MATRIX_P(Vertex_process::get_projection_matrix(fov, aspect_ratio, zNear, zFar));
			r.draw(TriLists, renderState[indicator] );
		}
		if (screen.screen_keys[VK_UP])
			view_pos.z() -= .05f;
		if (screen.screen_keys[VK_DOWN])
			view_pos.z() += .05f;
		if (screen.screen_keys[VK_LEFT])
			alpha += .5f;
		if (screen.screen_keys[VK_RIGHT])
			alpha -= .5f;

		if (screen.screen_keys[VK_SPACE]) {
			if (kbhit == 0) {
				kbhit = 1;
				if (++indicator >= 4)
					indicator = 0;
			}
		} else {
			kbhit = 0;
		}
		screen.screen_update();
//		Sleep(1);
	}

	// -----------------------------	save the last frame to the "output.png" file
	const char *filename = output_image.c_str();
	std::vector<unsigned char> image(screen.getFrameBuffer(),
	                                 screen.getFrameBuffer() + sizeof(unsigned char) * 4 * Height * Width);
	for (size_t j = 0; j < Height; ++j) {
		for (size_t i = 0; i < Width; ++i) {
			std::swap(image[j * 4 * Width + i * 4 + 0], image[j * 4 * Width + i * 4 + 2]);
		}
	}
	// Encode the image
	unsigned error = lodepng::encode(filename, image, Width, Height);
	// if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	return 0;
}