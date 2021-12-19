#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/
void sp_program1_1(FILE* fp) {
	float x0, x1;
	float y0, y1;
	int n;

	if (fp == NULL)
		return;

	
	printf("========================================\n");
	printf("=         Newton-Rapson Method         =\n");
	printf("========================================\n");
	scanf("%f", &x0);
	fprintf(fp,"%f", &x0);
	printf("%3s%16s%22s\n", "i", "xn1", "|f(xn1)|");
	fprintf(fp,"========================================\n");
	fprintf(fp, "=         Newton-Rapson Method         =\n");
	fprintf(fp, "========================================\n");
	fprintf(fp, "%3s%16s%22s\n", "i", "xn1", "|f(xn1)|");
	for (n = 0; n < Nmax; ++n)
	{
		y0 = _sp_f(x0);
		y1 = _sp_fp(x0);
		x1 = x0 - y0 / y1;
		printf("%3d%25.16e%13.4e\n", n, x0, fabs(y0));
		fprintf(fp, "%3d%25.16e%13.4e\n", n, x0, fabs(y0));

		if (fabs(x1) < DELTA || fabs(x1 - x0) < EPSILON)
		{
			break;
		}
		x0 = x1;
	}
}
