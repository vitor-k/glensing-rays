#include "GravitationalEntity.h"
#include "RungeKuttaSolver.h"
#include <cmath>

GravitationalEntity::GravitationalEntity(v3d center, float mass, float radius) : Sphere(center, radius), M(mass),
                                         schwarzschildRadius(2.f * G * M / (c * c) ), photonSphere(1.5f*schwarzschildRadius),
                                         relativeOuterRadius(outerRadius/schwarzschildRadius), relativePhotonSphere(photonSphere/schwarzschildRadius) {}


State3d GravitationalEntity::statePonto(const float& t, const State3d& estado) const {
	//const v3d raio = (estado.s - center);
	const double h2 = cross(estado.v, estado.s).norm2();
	return State3d{ estado.v, -1.5f * h2 * estado.s / pow(estado.s.norm2(), 2.5f) };
}


bool GravitationalEntity::response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) {
	const State3d inicial{ (intersection - center) / schwarzschildRadius , rayDirection };
	State3d final;

	if (useCache) {
		std::tuple<int, int, int> intersectionArredondado({ std::round(granularityMultiplier * intersection.x), std::round(granularityMultiplier * intersection.y), std::round(granularityMultiplier * intersection.z) });
		if (cachedResults.count(intersectionArredondado) > 0) {
			State3d final = cachedResults[intersectionArredondado];
			intersection = final.s * schwarzschildRadius + center;
			rayDirection = final.v;
			return false;
		}
		else if (blackCachedResults.count(intersectionArredondado) > 0) {
			pix = olc::Pixel(0, 0, 0);
			return true;
		}
	}
	final = RungeKuttaSolver::RungeKutta4Solverf(0.001f, 100000, inicial, (*this));
	//std::cout << (final.s - center).norm2() << std::endl;
	if ((final.s).norm() < 1.5) { //outerRadius * outerRadius) {
		if(useCache)
			blackCachedResults.emplace(std::make_tuple<int, int, int>(std::round(granularityMultiplier * intersection.x), std::round(granularityMultiplier * intersection.y), std::round(granularityMultiplier * intersection.z)));
		pix = olc::Pixel(0, 0, 0);
		return true;
	}
	else {
		if(useCache)
			cachedResults.try_emplace(std::make_tuple<int,int,int>(std::round(granularityMultiplier * intersection.x), std::round(granularityMultiplier * intersection.y), std::round(granularityMultiplier * intersection.z)), final);
		intersection = final.s*schwarzschildRadius + center;
		rayDirection = final.v;
		return false;
	}
}

