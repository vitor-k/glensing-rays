#pragma once
#include <cmath>
#include <functional>
#include "v3d.h"

class GravitationalEntity;

static class RungeKuttaSolver
{
public:
	static StateLight RungeKutta4Solverf(const float& step, const int& nSteps, const StateLight& initial, const GravitationalEntity& caller);

	template <typename T, class C>
	static T RungeKutta4Solver(const float& step, const int& nSteps, T initial, C& caller, T (C::*f)(float, T));

};
