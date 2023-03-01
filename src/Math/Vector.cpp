#include <Math/Vector.h>

std::ostream& operator<<(std::ostream& os, const Vector3d& v) {
	os << std::setprecision(4) << v[0] << "\t" << v[1] << "\t" << v[2] << std::endl;
	return os;
}

const double Vector3d::dot(const Vector3d& rhs) const {
	return _x * rhs.x() + _y * rhs.y() + _z * rhs.z();
}

const double Vector3d::norm() const {
	return std::sqrt(this->dot(*this));
}

Vector3d Vector3d::cwsiseProduct(const Vector3d& rhs) const {
	return Vector3d(rhs.x() * this->x(), rhs.y() * this->y(), rhs.z() * this->z());
}

const Vector3d Vector3d::cross(const Vector3d& rhs) const {

	Vector3d res;
	res[0] = _y * rhs.z() - _z * rhs.y();
	res[1] = _z * rhs.x() - _x * rhs.z();
	res[2] = _x * rhs.y() - _y * rhs.x();
	return res;
}

Vector3d Vector3d::operator+(const Vector3d& rhs) const {
	return Vector3d(_x + rhs.x(), _y + rhs.y(), _z + rhs.z());
}

Vector3d Vector3d::operator-(const Vector3d& rhs) const {
	return Vector3d(_x - rhs.x(), _y - rhs.y(), _z - rhs.z());
}

Vector3d Vector3d::operator/(const double rhs) const {
	return Vector3d(_x / rhs, _y / rhs, _z / rhs);
}

Vector3d operator*(const Vector3d& lhs, const double rhs) {
	return Vector3d(lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs);
}

Vector3d operator*(const double lhs, const Vector3d& rhs) {
	return Vector3d(rhs.x() * lhs, rhs.y() * lhs, rhs.z() * lhs);
}

Vector3d Vector3d::normalized() const
{
	return *this / norm();
}

std::ostream& operator<<(std::ostream& os, const Vector4f& v) {
	os << std::setprecision(4) << v[0] << "\t" << v[1] << "\t" << v[2] << "\t" << v[3] << std::endl;
	return os;
}

const double Vector4f::dot(const Vector4f& rhs) const {
	return _x * rhs.x() + _y * rhs.y() + _z * rhs.z() + _w * rhs.w();
}

const double Vector4f::norm() const {
	return std::sqrt(this->dot(*this));
}

const Vector3d to_vec3(const Vector4f& v) {
	return Vector3d(v.x(), v.y(), v.z());
}

const Vector4f to_vec4(const Vector3d& v, double w) {
	return Vector4f(v.x(), v.y(), v.z(), w);
}
