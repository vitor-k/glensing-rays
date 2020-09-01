#include "v3d.h"

//Euclidian norm
float v3d::norm() const {
	return std::sqrt(norm2());
}
//Returns normalized vector
v3d v3d::normalized() const {
	return *this / norm();
}
//Normalizes vector
void v3d::normalize() {
	*this /= norm();
}

v3d normalized(const v3d& vect){
	return vect.normalized();
}
std::ostream& operator<<(std::ostream& os, v3d vec) {
	return os << vec.x << ", " << vec.y << ", " << vec.z;
}