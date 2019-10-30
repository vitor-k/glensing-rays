#include "RungeKuttaSolver.h"


v3d RungeKuttaSolver::RungeKutta4Solver(double step, double tFinal, v3d initial, const std::function<v3d(double, v3d)>& f) {
	v3d current = initial;
	v3d next = initial;
	v3d k1, k2, k3, k4;

	for (double t=0; t < tFinal; t += step) {
		current = next;
		k1 = step * f(t, current);
		k2 = step * f(t + step / 2, current + k1 / 2);
		k3 = step * f(t + step / 2, current + k2 / 2);
		k4 = step * f(t + step, current + k3);
		next = current + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	}
	return next;
}