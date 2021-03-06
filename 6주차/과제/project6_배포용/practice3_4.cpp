#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_4(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = x[0] + x[1] + x[2] - 3.0;
		fvec[1] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5.0;
		fvec[2] = exp(x[0]) + x[0] * x[1] - x[0] * x[2] - 1.0;
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 1.0;						fjac[3] = 1.0;			fjac[6] = 1.0;
		fjac[1] = 2.0 * x[0];				fjac[4] = 2.0 * x[1];	fjac[7] = 2.0 * x[2];
		fjac[2] = exp(x[0]) + x[1] - x[2];	fjac[5] = x[0];			fjac[8] = -x[0];
		/********************************/
	}
}

void practice3_4(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.1, 1.2, 2.5 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-4.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-4.txt");
		return;
	}

	/********************************/
	printf("\n>>>>>>>>>> practice3_4 <<<<<<<<<\n");
	double ans = 0.0;
	printf("초기값 1 : x(0) = (0.1, 1.2, 2.5)\n");
	fprintf(fp_w, "초기값 1 : x(0) = (0.1, 1.2, 2.5)\n");
	x[0] = 0.1;
	x[1] = 1.2;
	x[2] = 2.5;
	hybrj1_(fcn3_4, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

	printf("x[0] = %lf	x[1] = %lf	x[2] = %lf\n", x[0], x[1], x[2]);
	fprintf(fp_w, "x[0] = %lf	x[1] = %lf	x[2] = %lf\n", x[0], x[1], x[2]);
	printf("info : %d\n", info);
	fprintf(fp_w, "info : %d\n", info);


	ans = x[0] + x[1] + x[2] - 3.0;
	printf("|f1(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f1(x)| = %lf\n", fabs(ans));
	ans = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5.0;
	printf("|f2(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f2(x)| = %lf\n", fabs(ans));
	ans = exp(x[0]) + x[0] * x[1] - x[0] * x[2] - 1.0;
	printf("|f3(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f3(x)| = %lf\n", fabs(ans));

	/////////////////////

	printf("초기값 2 : x(0) = (1.0, 0.0, 1.0)\n");
	fprintf(fp_w, "초기값 2 : x(0) = (1.0, 0.0, 1.0)\n");
	x[0] = 1.0;
	x[1] = 0.0;
	x[2] = 1.0;
	hybrj1_(fcn3_4, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

	printf("x[0] = %lf	x[1] = %lf	x[2] = %lf\n", x[0], x[1], x[2]);
	fprintf(fp_w, "x[0] = %lf	x[1] = %lf	x[2] = %lf\n", x[0], x[1], x[2]);
	printf("info : %d\n", info);
	fprintf(fp_w, "info : %d\n", info);

	ans = x[0] + x[1] + x[2] - 3.0;
	printf("|f1(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f1(x)| = %lf\n", fabs(ans));
	ans = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5.0;
	printf("|f2(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f2(x)| = %lf\n", fabs(ans));
	ans = exp(x[0]) + x[0] * x[1] - x[0] * x[2] - 1.0;
	printf("|f3(x)| = %lf\n", fabs(ans));
	fprintf(fp_w, "|f3(x)| = %lf\n", fabs(ans));
	/********************************/

	fclose(fp_w);
}
