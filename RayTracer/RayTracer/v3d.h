#pragma once
#include <iostream>


//3D vector

struct v3d {
	float x, y, z;
	v3d(float x, float y, float z) : x(x), y(y), z(z) {}
	//Operators
	inline v3d operator +(const v3d& vec) const { return v3d(x + vec.x, y + vec.y, z + vec.z); } 
	inline v3d operator -(const v3d& vec) const { return v3d(x - vec.x, y - vec.y, z - vec.z); } 
	inline v3d operator *(const float& numb) const { return v3d(x * numb, y * numb, z * numb); } 
	inline v3d operator /(const float& numb) const { return v3d(x / numb, y / numb, z / numb); } 
	//= Operatorn
	v3d& operator +=(const v3d& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	v3d& operator -=(const v3d& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	v3d& operator *=(const float& numb) {
		x *= numb;
		y *= numb;
		z *= numb;
		return *this;
	}
	v3d& operator /=(const float& numb) {
		x /= numb;
		y /= numb;
		z /= numb;
		return *this;
	}
	//Methods
	float dot(const v3d& vec) const {
		return x * vec.x + y * vec.y + z * vec.z;
	}
	float norm() {
		return sqrt(dot(*this));
	}
	v3d normalized() {
		return *this / norm();
	}
	void normalize() {
		*this /= norm();
	}
};

v3d operator *(const float& numb, const v3d& vec) {
	return vec * numb;
}
std::ostream& operator<<(std::ostream& os, v3d vec) {
	return os << vec.x << ", " << vec.y << ", " << vec.z;
}
