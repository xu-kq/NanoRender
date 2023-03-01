#include <Math/Matrix.h>

Comma_buffer operator<<(Matrix4d& m, double num) {
	m[0][0] = num;
	return Comma_buffer(m);
}

std::ostream& operator<<(std::ostream& os, const Matrix4d& rhs) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			os << std::setprecision(4) << rhs[i][j] << "\t";
		}
		os << std::endl;
	}
	return os;
}

Vector4f Matrix4d::operator*(const Vector4f& rhs) const {
	Vector4f ret;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ret[i] += _arr[i][j] * rhs[j];
		}
	}
	return ret;
}

Matrix4d Matrix4d::operator*(const Matrix4d& rhs) const {
	Matrix4d ret;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				ret[i][j] += _arr[i][k] * rhs[k][j];
			}
		}
	}
	return ret;
}

Matrix4d Matrix4d::transpose() const {
	Matrix4d ret;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ret[i][j] = this->operator[](j)[i];
		}
	}
	return ret;
}

void Matrix4d::swap_row(int i, int j) {
	for (int k = 0; k < 4; ++k) {
		std::swap(this->operator[](i)[k], this->operator[](j)[k]);
	}
}

Matrix4d Matrix4d::inverse() const {
	Matrix4d ret = Matrix4d::Identity();

	Matrix4d A(*this);
	for (int j = 0; j < 4; ++j) {
		int p = j;
		double maxV = std::abs(A[j][j]);
		for (int i = j + 1; i < 4; ++i) {
			if (maxV < std::abs(A[i][j])) {
				p = i;
				maxV = std::abs(A[i][j]);
			}
		}
		//if (maxV < 1e-20) {
		//	throw std::runtime_error("abnormal matrix");
		//}
		if (j != p) {
			A.swap_row(j, p);
			ret.swap_row(j, p);
		}
		double d = A[j][j];
		for (int i = j; i < 4; ++i) A[j][i] /= d;
		for (int i = 0; i < 4; ++i) ret[j][i] /= d;
		for (int i = 0; i < 4; ++i) {
			if (i != j) {
				double q = A[i][j];
				for (int k = j; k < 4; ++k) {
					A[i][k] -= q * A[j][k];
				}
				for (int k = 0; k < 4; ++k) {
					ret[i][k] -= q * ret[j][k];
				}
			}
		}
	}
		return ret;
}

std::array<std::array<double, 4>, 4> Matrix4d::identity = 
{	
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 
};