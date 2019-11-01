#include "RungeKuttaSolver.h"
#include "GravitationalEntity.h"

template <typename T, class C>
T RungeKuttaSolver::RungeKutta4Solver(const float& step, const int& nSteps, T initial, C& caller, T(C::* f)(float, T)) {
	T current = initial;
	T next = initial;
	T k1, k2, k3, k4;

	float t = 0;
	for (int st = 0; st < nSteps; st++) {
		current = next;
		k1 = step * (caller.*f)(t, current);
		k2 = step * (caller.*f)(t + step / 2, current + k1 / 2);
		k3 = step * (caller.*f)(t + step / 2, current + k2 / 2);
		k4 = step * (caller.*f)(t + step, current + k3);
		next = current + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		next.v.normalize();
		if ((next.s - caller.center).norm() < caller.schwarzschildRadius) { return next; }
		if ((next.s - caller.center).norm() > caller.outerRadius) { return next; }

		t += step;
	}
	return next;
}


State3d RungeKuttaSolver::RungeKutta4Solverf(const float& step, const int& nSteps, const State3d& initial, const GravitationalEntity& caller) {
	State3d current = initial;
	State3d next = initial;
	State3d k1, k2, k3, k4;
	float distToCenter;

	float t = 0;
	for (int st = 0; st < nSteps; st++) {
		current = next;
		k1 = step * caller.statePonto(t, current);
		k2 = step * caller.statePonto(t + step / 2, current + k1 / 2);
		k3 = step * caller.statePonto(t + step / 2, current + k2 / 2);
		k4 = step * caller.statePonto(t + step, current + k3);
		next = current + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		next.v.normalize();
		distToCenter = (next.s - caller.center).norm();
		if ((distToCenter < caller.photonSphere) || (distToCenter > caller.outerRadius) ){ 
			return next;
		}

		t += step;
	}
	return next;
}