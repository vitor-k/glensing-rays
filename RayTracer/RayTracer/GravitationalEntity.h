#pragma once
#include "Sphere.h"

//const float planckConstant = 6.62607015e34; // J*s   1
//const float c = 299792458; // m/s                    1
//const float G = 6.674e-11; // m^3/(kg*s^2)           1


class GravitationalEntity : public Sphere {
public:
	float M{ 0 };
	float schwarzschildRadius{ 0 };

	GravitationalEntity(v3d center, float outerRadius, float mass) : Sphere(center, outerRadius) , M(mass) {
		this->schwarzschildRadius = 2 * M;
	}

	/*GravitationalEntity(v3d center, float mass) : M(mass) {
		this->schwarzschildRadius = 2 * M;
		this->Sphere(center, outerRadius);
	} TODO */
};