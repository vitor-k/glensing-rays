// Standard 3D vector 

#pragma once
#include <iostream>
#include <cmath>

//3D vector

struct v3d {
	float x, y, z;

	constexpr v3d(const float& x,const float& y,const float& z) : x(x), y(y), z(z) {}
	constexpr v3d() : x(int()), y(int()), z(int()) {}

	//Operators

	constexpr v3d operator +(const v3d& vec) const { return v3d(x + vec.x, y + vec.y, z + vec.z); } 
	constexpr v3d operator -(const v3d& vec) const { return v3d(x - vec.x, y - vec.y, z - vec.z); }
	constexpr v3d operator *(const float& numb) const { return v3d(x * numb, y * numb, z * numb); }
	constexpr v3d operator /(const float& numb) const { return v3d(x / numb, y / numb, z / numb); }

	//= Operators

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

	//Other methods

	//Dot multiplication
	constexpr float dot(const v3d& vec) const {
		return x * vec.x + y * vec.y + z * vec.z;
	}
	//Cross multiplication
	constexpr v3d cross(const v3d& vec) const {
		return v3d(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}
	//Euclidian norm
	inline float norm() const {
		return std::sqrtf(norm2());
	}
	constexpr float norm2() const {
		return x*x + y*y + z*z;
	}
	//Returns normalized vector
	constexpr v3d normalized() const {
		return *this / norm();
	}
	//Normalizes vector
	constexpr void normalize() {
		*this /= norm();
	}
};

struct State3d {
	v3d s, v;
};

//More operators

constexpr v3d operator *(const float& numb, const v3d& vec) {
	return vec * numb;
}
std::ostream& operator<<(std::ostream& os, v3d vec) {
	return os << vec.x << ", " << vec.y << ", " << vec.z;
}

//Makes it easier to multiply vectors

constexpr v3d cross(const v3d& vec1, const v3d& vec2){
	return vec1.cross(vec2);
}
constexpr float dot(const v3d& vec1, const v3d& vec2){
	return vec1.dot(vec2);
}
constexpr v3d normalized(const v3d& vect){
	return vect.normalized();
}
