#pragma once
#include <cmath>
#include <functional>
#include "v3d.h"

static class RungeKuttaSolver
{
public:
	template <typename T, class C>
	static T RungeKutta4Solver(float step, float tFinal, T initial, C& caller, T (C::*f)(float, T));

};

template <typename T, class C>
T RungeKuttaSolver::RungeKutta4Solver(float step, float tFinal, T initial, C& caller, T (C::*f)(float, T)) {
	T current = initial;
	T next = initial;
	T k1, k2, k3, k4;

	for (float t = 0; t < tFinal; t += step) {
		current = next;
		k1 = step * (caller.*f)(t, current);
		k2 = step * (caller.*f)(t + step / 2, current + k1 / 2);
		k3 = step * (caller.*f)(t + step / 2, current + k2 / 2);
		k4 = step * (caller.*f)(t + step, current + k3);
		next = current + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	}
	return next;
}
