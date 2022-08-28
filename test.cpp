#include "Matrix.hpp"

int main() {
	Vector4f v0(1.f, 0, 0, 1);
	std::cout << "before rotate:" << std::endl;
	std::cout << v0 << std::endl;

	Matrix4f m;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j)	m[i][j] = 1;
		}
	}
	m[0][0] = 1.f/2, m[0][1] = -std::sqrt(3.f)/2;
	m[1][0] = std::sqrt(3.f) / 2, m[1][1] = 1.f/2;
	
	std::cout << "rotation matrix:" << std::endl;
	std::cout << m << std::endl;

	std::cout << "before rotate:" << std::endl;
	std::cout << m * v0 << std::endl;

	Matrix4f inv_m;
	inv_m[0][0] = 1.f / 2, inv_m[0][1] = std::sqrt(3.f) / 2;
	inv_m[1][0] = -std::sqrt(3.f) / 2, inv_m[1][1] = 1.f / 2;

	std::cout << "orthogonal matrix dot:" << std::endl;
	std::cout << m * inv_m << std::endl;

	return 0;
}