#include <Fragment/fragment.h>

Vector3d fragment_shader_BlinnPhong(const Vector3d& point, const Vector2d& texture,
                                    const Vector3d& normal) {
	Vector3d ka = Vector3d(0.005, 0.005, 0.005);
	Vector3d kd = {148. / 255, 121.0 / 255, 92.0 / 255 } ;
	Vector3d ks = Vector3d(0.7937, 0.7937, 0.7937);

	std::vector<Vector3d> l1 = {{20, 20, 20}, {500, 500, 500} };
	std::vector<Vector3d> l2 = {{-20, 20, 0}, {500, 500, 500} };

	std::vector<std::vector<Vector3d> > lights = {l1, l2  };
	Vector3d amb_light_intensity{10, 10, 10 };
	Vector3d eye_pos{0, 0, 10 };

	float p = 150;

	Vector3d result_color = {0, 0, 0 };
	for (auto& light : lights) {
		Vector3d Ld, Ls;
		Vector3d n, l, v, h, I;
		float R2;
		I = light[1];
		l = light[0] - point;
		n = normal.normalized();
		R2 = l.dot(l);
		v = (eye_pos - point).normalized();
		l = l.normalized();
		h = (v + l).normalized();

		Ld = kd.cwsiseProduct(I) / R2 * std::max(n.dot(l), 0.);
		Ls = ks.cwsiseProduct(I) / R2 * std::pow(std::max(n.dot(h), 0.), p);
		result_color = result_color + Ld + Ls;
	}
	result_color = result_color + ka.cwsiseProduct(amb_light_intensity);
	return result_color * 255.f;
}