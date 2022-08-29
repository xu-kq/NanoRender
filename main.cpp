#include"rasterizer.hpp"
#include<Vector.hpp>

int main() {
	const char* filename = "../../../image/output.png";
	Rasterizer r(filename, 700, 700);
	r.plot_line(Vector2i(0, 0), Vector2i(300, 200));
	r.show();
	return 0;
}