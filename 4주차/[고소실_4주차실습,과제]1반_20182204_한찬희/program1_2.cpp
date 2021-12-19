#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/
void program1_2(FILE* fp) {
	double x0, x1, temp;
	int n;

	if (fp == NULL)
		return;

	printf("========================================\n");
	printf("=             Scant Method             =\n");
	printf("========================================\n");
	scanf("%lf %lf", &temp, &x0);
	printf("%3s%16s%22s\n", "i", "xn1", "|f(xn1)|");
	fprintf(fp,"========================================\n");
	fprintf(fp, "=             Scant Method             =\n");
	fprintf(fp, "========================================\n");
	fprintf(fp, "%lf %lf", &temp, &x0);
	fprintf(fp, "%3s%16s%22s\n", "i", "xn1", "|f(xn1)|");
	
	
	for (n = 0; n < Nmax; ++n)
	{
		x1 = x0 - _f(x0) * (x0 - temp) / (_f(x0) - _f(temp));
		printf("%3d%25.16e%13.4e\n", n, x0, fabs(_f(x0)));
		fprintf(fp,"%3d%25.16e%13.4e\n", n, x0, fabs(_f(x0)));
		if (fabs(x1) < DELTA || fabs(x1 - x0) < EPSILON)
			break;
		temp = x0;
		x0 = x1;
	}

}
