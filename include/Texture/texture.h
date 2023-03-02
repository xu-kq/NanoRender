//
// Created by xukq on 23/03/02.
//
#pragma once
#include <iostream>
#include <vector>

#include <Loader_png/lodepng.h>
#include <Math/Vector.h>

class Texture {
public:
	Vector3d getColor(const Vector2d& coords) {
		auto u = coords.x(), v = coords.y();

		if(u >= 1) {
			u = 1;
		}
		if(u < 0) {
			u = 0;
		}
		if(v >= 1) {
			v = 1;
		}
		if(v < 0) {
			v = 0;
		}
		auto u_img = u * width;
		auto v_img = (1 - v) * height;
		return Vector3d(
			static_cast<int>(data[v_img * 4 * width + u_img * 4 + 0]),
			static_cast<int>(data[v_img * 4 * width + u_img * 4 + 1]),
			static_cast<int>(data[v_img * 4 * width + u_img * 4 + 2])
		) ;
	}
	Texture(const std::string &filename) : filename{filename} {
		auto& image = data; //the raw pixels
		unsigned width, height;
		//decode
		unsigned error = lodepng::decode(data, width, height, filename);
		//if there's an error, display it
		if (error)
			std::cout << "Texture decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

		//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
		for (size_t j = 0; j < height; ++j) {
			for (size_t i = 0; i < width; ++i) {
//				std::swap(image[j * 4 * width + i * 4 + 0], image[j * 4 * width + i * 4 + 2]);
			}
		}
		this->width = width;
		this->height = height;
	}
private:
	int width, height;
	std::vector<unsigned char> data;
	std::string filename;
};