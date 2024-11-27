#include "RungeKuttaSolver.h"
#include "GravitationalEntity.h"

template <typename T, class C>
T RungeKuttaSolver::RungeKutta4Solver(const float step, const int nSteps, const T& initial, const C& caller, T(C::* f)(const float&, const T&)) {
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

		t += step;
	}
	return next;
}


State3d RungeKuttaSolver::RungeKutta4Solverf(const float step, const int nSteps, const State3d& initial, const GravitationalEntity& caller) {
	State3d current = initial;
	State3d next = initial;
	State3d k1, k2, k3, k4;
	float distToCenter2;

	float t = 0.0f;
	for (int st = 0; st < nSteps; st++) {
		current = next;
		k1 = step * caller.statePonto(t, current);
		k2 = step * caller.statePonto(t + step * 0.5f, current + 0.5f * k1);
		k3 = step * caller.statePonto(t + step * 0.5f, current + 0.5f * k2);
		k4 = step * caller.statePonto(t + step, current + k3);
		next = current + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		next.v.normalize();
		distToCenter2 = (next.s).norm2();
		//std::cout << next.s.x << ", " << next.s.y << ", " << next.s.z << "  .  " << next.v.x << ", " << next.v.y << ", " << next.v.z << std::endl;
		if ((distToCenter2 < 2.25f) || (distToCenter2 > (caller.relativeOuterRadius2))) {
			return next;
		}

		t += step;
	}
	return next;
}