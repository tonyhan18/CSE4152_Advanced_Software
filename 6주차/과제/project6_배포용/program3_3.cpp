#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void f3_3(int* n, double* x, double* fvec, int* iflag)
{
	fvec[0] = (sin(x[0] * x[1] + M_PI / 6.0) + sqrt(x[0] * x[0] * x[1] * x[1] + 1.0)) / cos(x[0] - x[1]) + 2.8;
	fvec[1] = (x[0] * exp(x[0] * x[1] + M_PI / 6.0) - sin(x[0] - x[1])) / sqrt(x[0] * x[0] * x[1] * x[1] + 1.0) - 1.66;
}


void program3_3(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.0, 0.0 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;
	double ans = 0.0;

	printf("\n\n>>> Program3_3 Program <<<\n");
	FILE* fp_w = fopen("roots_found_3-3.txt", "w");
	if (fp_w == NULL)
	{
		printf("%s file open error...\n", "roots_found_3-3.txt");
		return;
	}

	x[0] = 20.0, x[1] = 0.0;
	printf("initial root : x1 = %lf, x2 =  %lf\n", x[0], x[1]);
	fprintf(fp_w, "initial root : x1 = %lf, x2 = %lf\n", x[0], x[1]);

	hybrd1_(f3_3, &n, x, fvec, &tol, &info, wa, &lwa);

	printf("x1 = %lf, x2 =  %lf\n", x[0], x[1]);
	printf("info is %d\n", info);

	fprintf(fp_w, "x1 = %lf, x2 =  %lf\n", x[0], x[1]);
	fprintf(fp_w, "info is %d\n", info);

	ans = (sin(x[0] * x[1] + M_PI / 6.0) + sqrt(x[0] * x[0] * x[1] * x[1] + 1.0)) / (cos(x[0] - x[1])) + 2.8;
	fprintf(fp_w, "|f1(x1, x2)| = %lf\n", fabs(ans));
	printf("|f1(x1, x2)| = %lf\n", fabs(ans));

	ans = (x[0] * exp(x[0] * x[1] + M_PI / 6.0) - sin(x[0] - x[1])) / sqrt(x[0] * x[0] * x[1] * x[1] + 1.0) - 1.66;
	fprintf(fp_w, "|f2(x1, x2)| = %lf\n", fabs(ans));
	printf("|f2(x1, x2)| = %lf\n", fabs(ans));
}
