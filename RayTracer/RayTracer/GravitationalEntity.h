#pragma once
#include "Sphere.h"
#include "RungeKuttaSolver.h"

//const float planckConstant = 6.62607015e34; // J*s   1
constexpr float c = 1; //299792458; // m/s
constexpr float G = 1; //6.674e-11; // m^3/(kg*s^2)

class GravitationalEntity : public Sphere {
public:
	float M{ 0 };
	float schwarzschildRadius{ 0 };

	GravitationalEntity(v3d center, float mass, float radius);
	GravitationalEntity(v3d center, float mass);
	State3d statePonto(float t, State3d estado);
	//bool intersect(const v3d& rayorigin, const v3d& rayDirection, v3d& intersection, v3d& normal) const override;
	bool response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) override;

};

State3d fazRK4(State3d inicial, GravitationalEntity& caller) {
	return RungeKuttaSolver::RungeKutta4Solver<State3d, GravitationalEntity>(0.001f, 100.1f, inicial, caller, &GravitationalEntity::statePonto);
}


GravitationalEntity::GravitationalEntity(v3d center, float mass, float radius) : Sphere(center, radius), M(mass){
		this->schwarzschildRadius = 2 * G * M / (c * c);
}

GravitationalEntity::GravitationalEntity(v3d center, float mass) : Sphere(center, 2 * G * M / (c * c)), M(mass), schwarzschildRadius(2 * G * M / (c * c)) {
	}

State3d GravitationalEntity::statePonto(float t, State3d estado) {
		v3d raio = (estado.s - center);
		State3d retorno{estado.v, raio.normalized()*(-G*M/raio.norm2())};
		return retorno;
}

//bool GravitationalEntity::intersect(const v3d& rayorigin, const v3d& rayDirection, v3d& intersection, v3d& normal) const{
//		// TODO
//}
bool GravitationalEntity::response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix){
		State3d inicial{intersection, rayDirection};

		using std::placeholders::_1;
		// State3d final = RungeKuttaSolver::RungeKutta4Solver<State3d>(0.01f, 0.1f, inicial, std::function<State3d(float, State3d)>( std::bind(&GravitationalEntity::statePonto , this, _1)));
		// State3d final = RungeKuttaSolver::RungeKutta4Solver<State3d, GravitationalEntity>(0.01f, 0.1f, inicial, this, &GravitationalEntity::statePonto);
		State3d final = fazRK4(inicial, (*this));
		//std::cout << (final.s - center).norm2() << std::endl;
		if ((final.s - center).norm() < schwarzschildRadius) { //outerRadius * outerRadius) {
			pix = olc::Pixel(0, 0, 0);
			return true;
		}
		else {
			intersection = final.s;
			rayDirection = final.v;
			return false;
		}
}

