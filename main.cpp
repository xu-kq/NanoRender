#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<vector>

struct Vertex {
	std::vector<float> v;
};
struct Face {
	std::vector<int> vertex_ind;
	std::vector<int> normal_ind;
	std::vector<int> texture_ind;
};
struct Normal {
	std::vector<float> n;
};
struct Texture {
	std::vector<float> t;
};
int main() {
	std::string ifile("../../../models/spot/spot_triangulated_good.obj");
	std::ifstream fin(ifile.data(), std::ifstream::in);
	std::string line_buffer;

	std::string type;
	std::string str;
	float coord;

	std::vector<Vertex> vertex_set;
	std::vector<Face> face_set;
	std::vector<Normal> normal_set;
	std::vector<Texture> texture_set;

	while (getline(fin, line_buffer)) {
		std::istringstream record(line_buffer);
		record >> type;
		if (type == "v") {
			Vertex vertex;
			while (record >> coord) {
				vertex.v.push_back(coord);
			}
			vertex_set.push_back(vertex);
		}
		if (type == "vn") {
			Normal normal;
			while (record >> coord) {
				normal.n.push_back(coord);
			}
			normal_set.push_back(normal);
		}
		if (type == "vt") {
			Texture texture;
			while (record >> coord) {
				texture.t.push_back(coord);
			}
			texture_set.push_back(texture);
		}
		if (type == "f") {
			Face face;
			while (record >> str) {
				std::size_t l = str.find_first_of("/");
				int v_ind, t_ind, n_ind;
				v_ind = std::stoi(std::string(str.begin(), str.begin() + l));
				std::size_t r = str.find_first_of("/", l + 1);
				t_ind = std::stoi(std::string(str.begin() + l + 1, str.begin() + r));
				n_ind = std::stoi(std::string(str.begin() + r + 1, str.end()));
				face.vertex_ind.push_back(v_ind);
				face.texture_ind.push_back(t_ind);
				face.normal_ind.push_back(n_ind);
			}
			face_set.push_back(face);
		}
	}
	for (auto& vertex : vertex_set) {
		if (vertex.v.size() != 3) {
			std::cout << "failed to load vertex data" << std::endl;
			return -1;
		}
	}
	for (auto& normal : normal_set) {
		if (normal.n.size() != 3) {
			std::cout << "failed to load normal data" << std::endl;
			return -1;
		}
	}
	for (auto& texture : texture_set) {
		if (texture.t.size() != 2) {
			std::cout << "failed to load texture data" << std::endl;
			return -1;
		}
	}
	for (auto& face : face_set) {
		if (face.vertex_ind.size() != 3 || face.normal_ind.size() != 3 || face.texture_ind.size() != 3) {
			std::cout << "failed to load face data" << std::endl;
			return -1;
		}
	}
	std::cout << "Successfully load: " << ifile << std::endl;
	return 0;
}