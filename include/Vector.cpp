#include"Vector.hpp"

std::ostream& operator<<(std::ostream& os, const Vector3f& v) {
	os << std::setprecision(4) << v[0] << "\t" << v[1] << "\t" << v[2] << std::endl;
	return os;
}

const float Vector3f::dot(const Vector3f& rhs) const {
	return _x * rhs.x() + _y * rhs.y() + _z * rhs.z();
}

const float Vector3f::norm() const {
	return std::sqrt(this->dot(*this));
}

const Vector3f Vector3f::cwsiseDot(float rhs) const {
	return Vector3f(rhs * this->x(), rhs * this->y(), rhs * this->z());
}

const Vector3f Vector3f::cross(const Vector3f& rhs) const {

	Vector3f res;
	res[0] = _y * rhs.z() - _z * rhs.y();
	res[1] = _z * rhs.x() - _x * rhs.z();
	res[2] = _x * rhs.y() - _y * rhs.x();
	return res;
}

Vector3f operator+(const Vector3f& lhs, const Vector3f& rhs) {
	return Vector3f(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

std::ostream& operator<<(std::ostream& os, const Vector4f& v) {
	os << std::setprecision(4) << v[0] << "\t" << v[1] << "\t" << v[2] << "\t" << v[3] << std::endl;
	return os;
}

const float Vector4f::dot(const Vector4f& rhs) const {
	return _x * rhs.x() + _y * rhs.y() + _z * rhs.z() + _w * rhs.w();
}

const float Vector4f::norm() const {
	return std::sqrt(this->dot(*this));
}

const Vector4f to_vec4(const Vector3f& v) {
	return Vector4f(v.x(), v.y(), v.z(), 1.f);
}
