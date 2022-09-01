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

Vector3f Vector3f::cwsiseProduct(const Vector3f& rhs) const {
	return Vector3f(rhs.x() * this->x(), rhs.y() * this->y(), rhs.z() * this->z());
}

const Vector3f Vector3f::cross(const Vector3f& rhs) const {

	Vector3f res;
	res[0] = _y * rhs.z() - _z * rhs.y();
	res[1] = _z * rhs.x() - _x * rhs.z();
	res[2] = _x * rhs.y() - _y * rhs.x();
	return res;
}

Vector3f Vector3f::operator+(const Vector3f& rhs) const {
	return Vector3f(_x + rhs.x(), _y + rhs.y(), _z + rhs.z());
}

Vector3f Vector3f::operator-(const Vector3f& rhs) const {
	return Vector3f(_x - rhs.x(), _y - rhs.y(), _z - rhs.z());
}

Vector3f Vector3f::operator/(const float rhs) const {
	return Vector3f(_x / rhs, _y / rhs, _z / rhs);
}

Vector3f operator*(const Vector3f& lhs, const float rhs) {
	return Vector3f(lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs);
}

Vector3f operator*(const float lhs, const Vector3f& rhs) {
	return Vector3f(rhs.x() * lhs, rhs.y() * lhs, rhs.z() * lhs);
}

Vector3f Vector3f::normalized() const
{
	return *this / norm();
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

const Vector3f to_vec3(const Vector4f& v) {
	return Vector3f(v.x(), v.y(), v.z());
}

const Vector4f to_vec4(const Vector3f& v, float w) {
	return Vector4f(v.x(), v.y(), v.z(), w);
}
