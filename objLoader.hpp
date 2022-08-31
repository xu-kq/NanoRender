#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<vector>


struct objLoader {
	objLoader(std::string s) : ifile(s) {
		std::ifstream fin(ifile.data(), std::ifstream::in);
		std::string line_buffer;

		std::string type;
		std::string str;
		float coord;

		while (getline(fin, line_buffer)) {
			std::istringstream record(line_buffer);
			record >> type;
			if (type == "v") {
				std::vector<float> v;
				while (record >> coord) {
					v.push_back(coord);
				}
				vertex_position.push_back(v);
			}
			if (type == "vn") {
				std::vector<float> n;
				while (record >> coord) {
					n.push_back(coord);
				}
				vertex_normal.push_back(n);
			}
			if (type == "vt") {
				std::vector<float> t;
				while (record >> coord) {
					t.push_back(coord);
				}
				vertex_texture.push_back(t);
			}
			if (type == "f") {
				std::vector<int> pInd, tInd, nInd;
				while (record >> str) {
					std::size_t l = str.find_first_of("/");
					int p_ind, t_ind, n_ind;
					p_ind = std::stoi(std::string(str.begin(), str.begin() + l));
					std::size_t r = str.find_first_of("/", l + 1);
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
		for (auto& vertex : vertex_position) {
			if (vertex.size() != 3) {
				std::cerr << "failed to load vertex data" << std::endl;
				throw std::runtime_error("failed to load vertex data");
				
			}
		}
		for (auto& normal : vertex_normal) {
			if (normal.size() != 3) {
				std::cerr << "failed to load normal data" << std::endl;
				throw std::runtime_error("failed to load normal data");
			}
		}
		for (auto& texture : vertex_texture) {
			if (texture.size() != 2) {
				std::cerr << "failed to load texture data" << std::endl;
				throw std::runtime_error("failed to load texture data");
			}
		}
		for (auto& face : position_ind) {
			if (face.size() != 3) {
				std::cerr << "failed to load position index" << std::endl;
				throw std::runtime_error("failed to load face data");
			}
		}
		for (auto& face : texture_ind) {
			if (face.size() != 3) {
				std::cerr << "failed to load texture index" << std::endl;
				throw std::runtime_error("failed to load face data");
			}
		}
		for (auto& face : normal_ind) {
			if (face.size() != 3) {
				std::cerr << "failed to load normal index" << std::endl;
				throw std::runtime_error("failed to load face data");
			}
		}
		std::cout << "Successfully load: " << ifile << std::endl;
	}


public:
	std::string ifile;

	std::vector<std::vector<float>> vertex_position;
	std::vector<std::vector<float>> vertex_texture;
	std::vector<std::vector<float>> vertex_normal;

	std::vector<std::vector<int>> position_ind;
	std::vector<std::vector<int>> texture_ind;
	std::vector<std::vector<int>> normal_ind;
};