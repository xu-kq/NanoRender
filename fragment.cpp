#include"fragment.hpp"

Vector3f fragment_shader_BlinnPhong(const Vector3f& point, const Vector2f& texture,
	const Vector3f& normal) {
	Vector3f ka = Vector3f(0.005f, 0.005f, 0.005f);
	Vector3f kd = { 148.f / 255, 121.0f / 255, 92.0f / 255 } ;
	Vector3f ks = Vector3f(0.7937f, 0.7937f, 0.7937f);

	std::vector<Vector3f> l1 = { {20, 20, 20}, {500, 500, 500} };
	std::vector<Vector3f> l2 = { {-20, 20, 0}, {500, 500, 500} };

	std::vector<std::vector<Vector3f> > lights = {  l1, l2  };
	Vector3f amb_light_intensity{ 10, 10, 10 };
	Vector3f eye_pos{ 0, 0, 10 };

	float p = 150;

	Vector3f result_color = { 0, 0, 0 };
	for (auto& light : lights) {
		Vector3f Ld, Ls;
		Vector3f n, l, v, h, I;
		float R2;
		I = light[1];
		l = light[0] - point;
		n = normal.normalized();
		R2 = l.dot(l);
		v = (eye_pos - point).normalized();
		l = l.normalized();
		h = (v + l).normalized();

		Ld = kd.cwsiseProduct(I) / R2 * std::max(n.dot(l), 0.f);
		Ls = ks.cwsiseProduct(I) / R2 * std::pow(std::max(n.dot(h), 0.f), p);
		result_color = result_color + Ld + Ls;
	}
	result_color = result_color + ka.cwsiseProduct(amb_light_intensity);
	return result_color * 255.f;
}