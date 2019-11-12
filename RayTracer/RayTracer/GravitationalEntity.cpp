#include "GravitationalEntity.h"
#include "RungeKuttaSolver.h"
#include <cmath>

GravitationalEntity::GravitationalEntity(v3d center, float mass, float radius) : Sphere(center, radius), M(mass),
                                         schwarzschildRadius(2 * G * M / (c * c) ), photonSphere(1.5*schwarzschildRadius){}


State3d GravitationalEntity::statePonto(const float& t, const State3d& estado) const {
	const v3d raio = (estado.s - center);
	return State3d{ estado.v, raio.normalized() * (-G * M / raio.norm2()) };
}


bool GravitationalEntity::response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
	const State3d inicial{ intersection, rayDirection };
	State3d final;

	if (cachedResults.count({std::round( 400*intersection.x), std::round(400*intersection.y) }) > 0) {
		State3d final = cachedResults[{std::round(400 * intersection.x), std::round(400 * intersection.y) }];
		intersection = final.s;
		rayDirection = final.v;
		return false;
	}
	else if (blackCachedResults.count({ std::round(400 * intersection.x), std::round(400 * intersection.y) }) > 0) {
		pix = olc::Pixel(0, 0, 0);
		return true;
	}
	final = RungeKuttaSolver::RungeKutta4Solverf(0.001f, 100000, inicial, (*this));
	//std::cout << (final.s - center).norm2() << std::endl;
	if ((final.s - center).norm() < photonSphere) { //outerRadius * outerRadius) {
		blackCachedResults.emplace(std::make_pair<int, int>(std::round(400 * intersection.x), std::round(400 * intersection.y)));
		pix = olc::Pixel(0, 0, 0);
		return true;
	}
	else {
		cachedResults.try_emplace(std::make_pair<int,int>(std::round(400 * intersection.x), std::round(400 * intersection.y)), final);
		intersection = final.s;
		rayDirection = final.v;
		return false;
	}
}

