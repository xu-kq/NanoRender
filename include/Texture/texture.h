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
		int u_img = u * width;
		int v_img = (1 - v) * height;
		return Vector3d(
			data[v_img * 4 * width + u_img * 4 + 0],
			data[v_img * 4 * width + u_img * 4 + 1],
			data[v_img * 4 * width + u_img * 4 + 2]
		);
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
		this->width = width;
		this->height = height;
	}
private:
	int width, height;
	std::vector<unsigned char> data;
	std::string filename;
};