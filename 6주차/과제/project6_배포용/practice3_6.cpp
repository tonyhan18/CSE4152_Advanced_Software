#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_6(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag) {
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = 3.0 * x[0] * x[0] - 2.0 * x[1] * x[1] - 1.0;
		fvec[1] = x[0] * x[0] - 2 * x[0] + x[1] * x[1] + 2.0 * x[1] - 8.0;
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 6 * x[0];			fjac[2] = -4.0 * x[1];
		fjac[1] = 2 * x[0] - 2.0;	fjac[3] = 2.0 * x[1] + 2.0;
		/********************************/
	}
}

void practice3_6(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-6.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-6.txt");
		return;
	}

	/********************************/
	printf("\n>>>>>>>>>> practice3_6 <<<<<<<<<\n");
	double ans1 = 0.0;
	double ans2 = 0.0;

	for (int i = -4; i <= 4; ++i)
	{
		for (int j = 5; j >= -5; --j)
		{
			x[0] = i;
			x[1] = j;
			hybrj1_(fcn3_6, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
			if (info == 1)
			{
				ans1 = 3.0 * x[0] * x[0] - 2.0 * x[1] * x[1] - 1.0;
				ans2 = x[0] * x[0] - 2.0 * x[0] + x[1] * x[1] + 2.0 * x[1] - 8.0;
				printf("|f1(x)| = %lf, |f2(x)| = %lf,		x[0], x[1] = %lf, %lf\n", fabs(ans1), fabs(ans2), x[0], x[1]);
				fprintf(fp_w, "|f1(x)| = %lf, |f2(x)| = %lf,		x[0], x[1] = %lf, %lf\n", fabs(ans1), fabs(ans2), x[0], x[1]);
			}
		}
	}
	/********************************/

	fclose(fp_w);
}