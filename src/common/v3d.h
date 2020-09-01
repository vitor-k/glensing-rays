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
	constexpr float norm2() const {
		return x*x + y*y + z*z;
	}
	//Euclidian norm
	float norm() const;
	//Returns normalized vector
	v3d normalized() const;
	//Normalizes vector
	void normalize();
};

//More operators

constexpr v3d operator *(const float& numb, const v3d& vec) {
	return vec * numb;
}

//Makes it easier to multiply vectors

constexpr v3d cross(const v3d& vec1, const v3d& vec2){
	return vec1.cross(vec2);
}
constexpr float dot(const v3d& vec1, const v3d& vec2){
	return vec1.dot(vec2);
}


struct State3d {
	v3d s, v;

	constexpr State3d operator/(const float& numb);
	constexpr State3d operator+(const State3d& other);
};
constexpr State3d operator *(const float& numb, const State3d& state) {
	return { numb * state.s, numb * state.v };
}
constexpr State3d State3d::operator/(const float& numb) {
	return { s/numb, v/numb };
}
constexpr State3d State3d::operator+(const State3d& other) {
	return { s + other.s, v + other.v };
}
