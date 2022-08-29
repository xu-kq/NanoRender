#include"Vector.hpp"


std::ostream& operator<<(std::ostream& os, Vector3f v) {
	os << v[0] << "\n" << v[1] << "\n" << v[2];
	return os;
}

float Vector3f::dot(const Vector3f& rhs) const {
	return _x * rhs.x() + _y * rhs.y() + _z * rhs.z();
}

float Vector3f::norm() const {
	return std::sqrt(this->dot(*this));
}

Vector3f Vector3f::cross(const Vector3f& rhs) const {

	Vector3f res;
	res[0] = _y * rhs.z() - _z * rhs.y();
	res[1] = _z * rhs.x() - _x * rhs.z();
	res[2] = _x * rhs.y() - _y * rhs.x();
	return res;
}



std::ostream& operator<<(std::ostream& os, Vector4f v) {
	os << std::setprecision(4) << v[0] << "\n" << v[1] << "\n" << v[2] << "\n" << v[3] << std::endl;
	return os;
}

float Vector4f::dot(const Vector4f& rhs) const {
	return _x * rhs.x() + _y * rhs.y() + _z * rhs.z() + _w * rhs.w();
}

float Vector4f::norm() const {
	return std::sqrt(this->dot(*this));
}