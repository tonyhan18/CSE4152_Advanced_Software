#define _USE_MATH_DEFINES
#include <math.h>

double _f1(double x) {
	//f1 = x ^ 2 - 4x + 4 - lnx = 0
	double ans = pow(x, 2) - (4 * x) + 4 - log(x);
	return ans;
}

double _fp1(double x) {
	//f1 = 2x - 4 - 1 / x = 0
	double ans = 2*x - 4 - 1/x;
	return ans;
}

double _f2(double x) {
	// f2 = x +1 -2sin(PI*x) = 0
	double ans = x + 1 - (2 * sin(M_PI * x));
	return ans;
}

double _fp2(double x) {
	// f2 = 1 -2cos(PI*x) * PI = 0
	double ans = 1 - (2 * cos(M_PI * x) * M_PI);
	return ans;
}

double _f3(double x) {
	// f3 = x^4 -11.0x^3 +42.35x^2 -66.55x +35.1384 = 0
	double ans = pow(x, 4) - (11 * pow(x, 3)) + (42.35 * pow(x, 2)) - (66.55 * x) + 35.1384;
	return ans;
}

double _fp3(double x) {
	// f3 = 4x^3 - 33.0x^2 +84.70x -66.55= 0
	double ans = 4.0 * pow(x, 3) - (33.0 * pow(x, 2)) + (84.70 * x) - 66.55;
	return ans;
}

double _f_sqrt(double x) {
	return x * x - 2.0;
}

double _fp_sqrt(double x) {
	return 2.0 * x;
}

double _f_vehicle(double x) {
	double l, h, D, beta;
	double A, B, C, E;

	l = 89;
	h = 49;
	D = 55;
	beta = 11.5;

	A = l * sin(beta);
	B = l * cos(beta);
	C = (h + 0.5 * D) * sin(beta) - 0.5 * D * tan(beta);
	E = (h + 0.5 * D) * cos(beta) - 0.5 * D;

	return A * sin(x) * cos(x) + B * sin(x) * sin(x) - C * cos(x) - E * sin(x);
}

double _fp_vehicle(double x) {
	double l, h, D, beta;
	double A, B, C, E;
	l = 89;
	h = 49;
	D = 55;
	beta = 11.5;

	A = l * sin(beta);
	B = l * cos(beta);
	C = (h + 0.5 * D) * sin(beta) - 0.5 * D * tan(beta);
	E = (h + 0.5 * D) * cos(beta) - 0.5 * D;

	return A * (cos(x) * cos(x) - sin(x) * sin(x)) + B * 2 * sin(x) * cos(x) + C * sin(x) - E * cos(x);
}

double _f_comp(double x) {
	return (log(x) - 1);
}

double _fp_comp(double x) {
	return (1/x);
}

