#pragma once
#include "Sphere.h"

//const float planckConstant = 6.62607015e34; // J*s   1
constexpr float c = 1; //299792458; // m/s
constexpr float G = 1; //6.674e-11; // m^3/(kg*s^2)

class GravitationalEntity : public Sphere {
public:
	float M{ 0 };
	float schwarzschildRadius{ 0 };

	GravitationalEntity(v3d center, float mass, float radius) : Sphere(center, radius), M(mass){
		this->schwarzschildRadius = 2 * G * M / (c * c);
	}

	GravitationalEntity(v3d center, float mass) : Sphere(center, 2 * G * M / (c * c)), M(mass), schwarzschildRadius(2 * G * M / (c * c)) {
	}

	State3d statePonto(float t, State3d estado) {
		v3d raio = (estado.s - center);
		State3d retorno{estado.v, raio.normalized()*(-G*M/raio.norm2())};
		return retorno;
	}

	bool intersect(const v3d& rayorigin, const v3d& rayDirection, v3d& intersection, v3d& normal) const override {
		// TODO
	}
	bool response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) override{
		pix = olc::Pixel(0, 0, 0);
		return true;
	}
};