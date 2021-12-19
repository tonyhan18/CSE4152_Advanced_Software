#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_5(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/

	fvec[0] = 10.0 * x[0] - 2.0 * x[1] * x[1] + x[1] - 2.0 * x[2] - 5.0;
	fvec[1] = 8.0 * x[1] * x[1] + 4.0 * x[2] * x[2] - 9.0;
	fvec[2] = 8.0 * x[1] * x[2] + 4.0;

	/********************************/
}

void practice3_5(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 1.0, -1.0, 1.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-5.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-5.txt");
		return;
	}

	/********************************/
	printf("\n>>>>>>>>>> practice3_5 <<<<<<<<<\n");
	double ans = 0.0;
	printf("�ʱⰪ 1 : x(0) = (1.0, -1.0, 1.0)\n");
	fprintf(fp_w, "�ʱⰪ 1 : x(0) = (1.0, -1.0, 1.0)\n");
	x[0] = 1.0;
	x[1] = -1.0;
	x[2] = 1.0;
	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);

	printf("x[0] = %lf	x[1] = %lf	x[2] = %lf\n", x[0], x[1], x[2]);
	fprintf(fp_w, "x[0] = %lf	x[1] = %lf	x[2] = %lf\n", x[0], x[1], x[2]);
	printf("info : %d\n", info);
	fprintf(fp_w, "info : %d\n", info);


	ans = 10.0 * x[0] - 2.0 * x[1] * x[1] + x[1] - 2.0 * x[2] - 5.0;
	printf("|f1(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f1(x)| = %lf\n", fabs(ans));
	ans = 8.0 * x[1] * x[1] + 4.0 * x[2] * x[2] - 9.0;
	printf("|f2(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f2(x)| = %lf\n", fabs(ans));
	ans = 8.0 * x[1] * x[2] + 4.0;
	printf("|f3(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f3(x)| = %lf\n", fabs(ans));

	/////////////////////

	printf("�ʱⰪ 2 : x(0) = (1.0, 1.0, -1.0)\n");
	fprintf(fp_w, "�ʱⰪ 2 : x(0) = (1.0, 1.0, -1.0)\n");
	x[0] = 1.0;
	x[1] = 1.0;
	x[2] = -1.0;
	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);

	printf("x[0] = %lf	x[1] = %lf	x[2] = %lf\n", x[0], x[1], x[2]);
	fprintf(fp_w, "x[0] = %lf	x[1] = %lf	x[2] = %lf\n", x[0], x[1], x[2]);
	printf("info : %d\n", info);
	fprintf(fp_w, "info : %d\n", info);

	ans = 10.0 * x[0] - 2.0 * x[1] * x[1] + x[1] - 2.0 * x[2] - 5.0;
	printf("|f1(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f1(x)| = %lf\n", fabs(ans));
	ans = 8.0 * x[1] * x[1] + 4.0 * x[2] * x[2] - 9.0;
	printf("|f2(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f2(x)| = %lf\n", fabs(ans));
	ans = 8.0 * x[1] * x[2] + 4.0;
	printf("|f3(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f3(x)| = %lf\n", fabs(ans));
	/********************************/

	fclose(fp_w);
}