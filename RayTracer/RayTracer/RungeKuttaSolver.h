#pragma once
#include <cmath>
#include <functional>
#include "v3d.h"

static class RungeKuttaSolver
{
	static v3d RungeKutta4Solver(double step, double tFinal, v3d initial, const std::function<v3d(double, v3d)>& f);

};

