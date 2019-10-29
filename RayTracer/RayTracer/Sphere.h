#pragma once
#include "v3d.h"

//Sphere

class Sphere {
public:
	v3d center;
	float outerRadius;
	Sphere(v3d center, float outerRadius) : center(center), outerRadius(outerRadius) {}

	bool intersect(const v3d& rayorigin, const v3d& rayDirection, v3d& intersection, v3d& normal) const{
		// Based on the code in medium.com/farouk-ounanes-home-on-the-internet/ray-tracer-in-c-from-scratch-e013269884b6
		v3d v = rayorigin - center;
		const float b = 2 * v.dot(rayDirection);
		const float c = v.norm2() - outerRadius*outerRadius;
		const float delta = b*b - 4 * c;

		if (delta < 0) return false; // If delta is negative, the ray doesn`t intersect 

		const float t = (-b - sqrt(delta)) / 2;

		if (t<0) return false; // If t is negative, the ray intersects before the ray origin

		intersection = rayorigin + t*rayDirection;

		normal = (intersection - center) / outerRadius; // Normal vector to the surface in the intersection

		return true;
	}

	virtual bool response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) = 0 {}
};

class MirroredSphere : public Sphere {
public:
	MirroredSphere(v3d center, float outerRadius) : Sphere(center, outerRadius) {}
	bool response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
		rayDirection = rayDirection - 2 * dot(rayDirection, intersectionNormal) * intersectionNormal;
		return false;
	}
};

class OpaqueSphere : public Sphere {
public:
	int32_t R, G, B;
	OpaqueSphere(v3d center, float outerRadius, int32_t R, int32_t G, int32_t B) : Sphere(center, outerRadius), R(R), G(G), B(B) {}
	bool response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
		float normalMultiplier = abs(rayDirection.dot(intersectionNormal));
		pix = olc::Pixel(R*normalMultiplier, G*normalMultiplier, B*normalMultiplier);
		return true;
	}
};

class CoolSphere : public Sphere {
public:
	CoolSphere(v3d center, float outerRadius) : Sphere(center, outerRadius) {}
	bool response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
		v3d cool = cross(rayDirection, intersectionNormal) ;
		pix = olc::Pixel(125 + 125*cool.x, 125 + 125*cool.y, 125 + 125*cool.z);
		return true;
	}

};