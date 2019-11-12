#pragma once
#include "Sphere.h"
#include "olcPixelGameEngine.h"
#include "v3d.h"
#include<map>
#include<set>
#include<utility>

//const float planckConstant = 6.62607015e34; // J*s   1
constexpr float c = 1; //299792458; // m/s
constexpr float G = 1; //6.674e-11; // m^3/(kg*s^2)

class GravitationalEntity : public Sphere {
public:
	const float M{ 0 };
	const float schwarzschildRadius{ 0 };
	const float photonSphere{ 0 };

	GravitationalEntity(v3d center, float mass, float radius);
	State3d statePonto(const float& t, const State3d& estado) const;
	bool response(v3d& rayDirection, v3d& intersection, v3d& intersectionNormal, olc::Pixel& pix) override;

	std::map<std::pair<int,int>, State3d> cachedResults;
	std::set<std::pair<int, int>> blackCachedResults;
};
