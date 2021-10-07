#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp) {
	static double x0, x1;
	double y0, y1;
	int n;

	if (fp == NULL)
		return;

	scanf("%lf", &x0);
	printf("========================================\n");
	printf("=         Newton-Rapson Method         =\n");
	printf("========================================\n");
	fprintf(fp,"========================================\n");
	fprintf(fp, "=         Newton-Rapson Method         =\n");
	fprintf(fp, "========================================\n");
	printf("%3s%16s%22s\n","i","xn1","|f(xn1)|");
	fprintf(fp,"%3s%16s%22s\n", "i", "xn1", "|f(xn1)|");
	for (n = 0; n < Nmax; ++n)
	{
		y0 = _f(x0);
		y1 = _fp(x0);
		x1 = x0 - y0 / y1;
		printf("%3d%25.16e%13.4e\n", n, x0, fabs(y0));
		fprintf(fp,"%3d%25.16e%13.4e\n", n, x0, fabs(y0));


		if (fabs(x1) < DELTA || fabs(x1 - x0) < EPSILON)
		{
			break;
		}
		x0 = x1;
	}
}
