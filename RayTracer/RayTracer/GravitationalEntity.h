#pragma once

const double planckConstant = 6.62607015e34; // J*s
const double c = 299792458; // m/s
const double G = 6.674e-11; // m^3/(kg*s^2)


class GravitationalEntity {
public:
	double M{ 0 };
	double schwarzschildRadius{ 0 };
	double radius;

	GravitationalEntity(double mass) : M(mass) {
		this->schwarzschildRadius = 2 * G * M / (c * c);
		this->radius = this->schwarzschildRadius;
	}
	GravitationalEntity(double mass, double radius) {
		this->schwarzschildRadius = 2 * G * M / (c * c);
		this->radius = radius;
	}
};