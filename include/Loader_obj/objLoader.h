#pragma once
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<vector>

#include<Math/Vector.h>

struct objLoader {
	objLoader(std::string s) : ifile(s) {
		std::ifstream fin(ifile.data(), std::ifstream::in);
		std::string line_buffer;

		std::string type;
		std::string str;
		double coord;

		while (getline(fin, line_buffer)) {
			std::istringstream record(line_buffer);
			record >> type;
			if (type == "v") {
				std::vector<double> v;
				while (record >> coord) {
					v.push_back(coord);
				}
				vertex_position.emplace_back(v);
			}
			if (type == "vn") {
				std::vector<double> n;
				while (record >> coord) {
					n.push_back(coord);
				}
				vertex_normal.emplace_back(n);
			}
			if (type == "vt") {
				std::vector<double> t;
				while (record >> coord) {
					t.push_back(coord);
				}
				vertex_texture.emplace_back(t);
			}
			if (type == "f") {
				std::vector<int> pInd, tInd, nInd;
				while (record >> str) {
					std::size_t l = str.find_first_of('/');
					int p_ind, t_ind, n_ind;
					p_ind = std::stoi(std::string(str.begin(), str.begin() + l));
					std::size_t r = str.find_first_of('/', l + 1);
					t_ind = std::stoi(std::string(str.begin() + l + 1, str.begin() + r));
					n_ind = std::stoi(std::string(str.begin() + r + 1, str.end()));
					pInd.push_back(p_ind - 1);
					tInd.push_back(t_ind - 1);
					nInd.push_back(n_ind - 1);
				}
				position_ind.push_back(pInd);
				texture_ind.push_back(tInd);
				normal_ind.push_back(nInd);
			}
		}
		std::cout << "Successfully load: " << ifile << std::endl;
	}

public:
	std::string ifile;

	std::vector<Vector3d> vertex_position;
	std::vector<Vector2d> vertex_texture;
	std::vector<Vector3d> vertex_normal;

	std::vector<std::vector<int>> position_ind;
	std::vector<std::vector<int>> texture_ind;
	std::vector<std::vector<int>> normal_ind;
};