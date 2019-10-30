#pragma once

const float planckConstant = 6.62607015e34; // J*s
const float c = 299792458; // m/s
const float G = 6.674e-11; // m^3/(kg*s^2)


class GravitationalEntity {
public:
	float M{ 0 };
	float schwarzschildRadius{ 0 };
	float radius;

	GravitationalEntity(float mass) : M(mass) {
		this->schwarzschildRadius = 2 * G * M / (c * c);
		this->radius = this->schwarzschildRadius;
	}
	GravitationalEntity(float mass, float radius) {
		this->schwarzschildRadius = 2 * G * M / (c * c);
		this->radius = radius;
	}
};