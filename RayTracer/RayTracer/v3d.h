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
	inline float dot(const v3d& vec) const {
		return x * vec.x + y * vec.y + z * vec.z;
	}
	inline v3d cross(const v3d& vec) const {
		return v3d(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}
	inline float norm() {
		return sqrt(dot(*this));
	}
	inline v3d normalized() {
		return *this / norm();
	}
	inline void normalize() {
		*this /= norm();
	}
};

inline v3d operator *(const float& numb, const v3d& vec) {
	return vec * numb;
}
std::ostream& operator<<(std::ostream& os, v3d vec) {
	return os << vec.x << ", " << vec.y << ", " << vec.z;
}
inline float dot(const v3d& vec1, const v3d& vec2) {
	return vec1.dot(vec2);
}
inline v3d cross(const v3d& vec1, const v3d& vec2) {
	return vec1.cross(vec2);
}