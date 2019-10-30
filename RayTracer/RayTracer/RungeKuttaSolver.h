#pragma once
#include <cmath>
#include <functional>
#include "v3d.h"

static class RungeKuttaSolver
{
	template <typename T>
	static T RungeKutta4Solver(float step, float tFinal, T initial, const std::function<T(float, T)>& f);

};

template <typename T>
T RungeKuttaSolver::RungeKutta4Solver(float step, float tFinal, T initial, const std::function<T(float, T)>& f) {
	T current = initial;
	T next = initial;
	T k1, k2, k3, k4;

	for (float t = 0; t < tFinal; t += step) {
		current = next;
		k1 = step * f(t, current);
		k2 = step * f(t + step / 2, current + k1 / 2);
		k3 = step * f(t + step / 2, current + k2 / 2);
		k4 = step * f(t + step, current + k3);
		next = current + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	}
	return next;
}
