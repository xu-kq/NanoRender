#include <Loader_obj/objLoader.h>

void objLoader::read(std::string& s) {
	ifile = s;
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
			vPosition.emplace_back(v);
		}
		if (type == "vn") {
			std::vector<double> n;
			while (record >> coord) {
				n.push_back(coord);
			}
			vNormal.emplace_back(n);
		}
		if (type == "vt") {
			std::vector<double> t;
			while (record >> coord) {
				t.push_back(coord);
			}
			vTexture.emplace_back(t);
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
			indPosition.push_back(pInd);
			indTexture.push_back(tInd);
			indNormal.push_back(nInd);
		}
	}
	std::cout << "Successfully load: " << ifile << std::endl;
}