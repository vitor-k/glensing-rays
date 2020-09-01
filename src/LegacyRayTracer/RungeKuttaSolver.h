#pragma once
#include <cmath>
#include <functional>
#include "common/v3d.h"

class GravitationalEntity;

class RungeKuttaSolver
{
public:
	static State3d RungeKutta4Solverf(const float& step, const int& nSteps, const State3d& initial, const GravitationalEntity& caller);

	template <typename T, class C>
	static T RungeKutta4Solver(const float& step, const int& nSteps, const T& initial, const C& caller, T (C::*f)(const float&, const T&));

};
