#pragma once
#include <iostream>
#include <cmath>

//3D vector

struct v3d {
	float x, y, z;
	constexpr v3d(const float& x,const float& y,const float& z) : x(x), y(y), z(z) {}
	//Operators
	constexpr v3d operator +(const v3d& vec) const { return v3d(x + vec.x, y + vec.y, z + vec.z); } 
	constexpr v3d operator -(const v3d& vec) const { return v3d(x - vec.x, y - vec.y, z - vec.z); }
	constexpr v3d operator *(const float& numb) const { return v3d(x * numb, y * numb, z * numb); }
	constexpr v3d operator /(const float& numb) const { return v3d(x / numb, y / numb, z / numb); }
	//= Operatorn
	constexpr v3d& operator +=(const v3d& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	constexpr v3d& operator -=(const v3d& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	constexpr v3d& operator *=(const float& numb) {
		x *= numb;
		y *= numb;
		z *= numb;
		return *this;
	}
	constexpr v3d& operator /=(const float& numb) {
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
		return std::sqrtf(dot(*this));
	}
	inline float norm2() {
		return dot(*this);
	}
	inline v3d normalized() {
		return *this / norm();
	}
	inline void normalize() {
		*this /= norm();
	}
};

constexpr v3d operator *(const float& numb, const v3d& vec) {
	return vec * numb;
}
std::ostream& operator<<(std::ostream& os, v3d vec) {
	return os << vec.x << ", " << vec.y << ", " << vec.z;
}