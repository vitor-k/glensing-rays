#include "GravitationalEntity.h"
#include "RungeKuttaSolver.h"


GravitationalEntity::GravitationalEntity(v3d center, float mass, float radius) : Sphere(center, radius), M(mass),
                                         schwarzschildRadius(2 * G * M / (c * c) ), photonSphere(1.5*schwarzschildRadius),
                                         relativeOuterRadius(outerRadius/schwarzschildRadius), relativePhotonSphere(photonSphere/schwarzschildRadius) {}


State3d GravitationalEntity::statePonto(const float& t, const State3d& estado) const {
	//const v3d raio = (estado.s - center);
	const double h2 = cross(estado.v, estado.s).norm2();
	return State3d{ estado.v, -1.5 * h2 * estado.s / pow(estado.s.norm2(), 2.5) };
}


bool GravitationalEntity::response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
	const State3d inicial{ (intersection - center) / schwarzschildRadius , rayDirection };

	//std::cout << "Novo: " << inicial.s.x << ", " << inicial.s.y << ", " << inicial.s.z << "  .  " << inicial.v.x << ", " << inicial.v.y << ", " << inicial.v.z << std::endl;
	State3d final = RungeKuttaSolver::RungeKutta4Solverf(0.01f, 100000, inicial, (*this));
	//std::cout << "Final: " << final.s.x << ", " << final.s.y << ", " << final.s.z << "  .  " << final.v.x << ", " << final.v.y << ", " << final.v.z << std::endl;

	if ((final.s).norm() < 1.5) { //outerRadius * outerRadius) {
		pix = olc::Pixel(0, 0, 0);
		return true;
	}
	else {
		intersection = final.s*schwarzschildRadius + center;
		rayDirection = final.v;
		return false;
	}
}

