#include "RungeKuttaSolver.h"


v3d RungeKuttaSolver::RungeKutta4Solver(double step, double tFinal, v3d initial, const std::function<v3d(double, v3d)>& f) {
	double t = 0;
	v3d current = initial;
	v3d k1 = step * f(t, current);
	v3d k2 = step * f(t+ step / 2, current + k1 / 2);
	v3d k3 = step * f(t+ step / 2, current + k2 / 2);
	v3d k4 = step * f(t+ step, current + k3);

	v3d next = current + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	t += step;

	for (; t < tFinal; t += step) {
		current = next;
		k1 = step * f(t, current);
		k2 = step * f(t + step / 2, current + k1 / 2);
		k3 = step * f(t + step / 2, current + k2 / 2);
		k4 = step * f(t + step, current + k3);
		next = current + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	}
	return next;
}