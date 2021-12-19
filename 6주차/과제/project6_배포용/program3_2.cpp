#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void f3_2(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1)
	{
		/********************************/
		fvec[0] = x[0] + 10.0 * x[1] + 9.0;
		fvec[1] = sqrt(5.0) * (x[3] - x[2]) - 2.0 * sqrt(5.0);
		fvec[2] = (x[1] - 2.0 * x[2]) * (x[1] - 2.0 * x[2]) - 9.0;
		fvec[3] = sqrt(10.0) * (x[0] - x[3]) * (x[0] - x[3]) - 2.0 * sqrt(10.0);
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2)
	{
		/********************************/
		fjac[0] = 1.0;									fjac[4] = 10.0 * x[1];				fjac[8] = 0.0;						 fjac[12] = 0.0;
		fjac[1] = 0.0;									fjac[5] = 0.0;						fjac[9] = sqrt(5.0) * x[2];			 fjac[13] = -sqrt(5.0) * x[3];
		fjac[2] = 0.0;									fjac[6] = 2.0 * x[1] - 4.0 * x[2];	fjac[10] = 8.0 * x[2] - 4.0 * x[1];  fjac[14] = 0.0;
		fjac[3] = 2.0 * sqrt(10.0) * (x[0] - x[3]);		fjac[7] = 0.0;						fjac[11] = 0.0;						 fjac[15] = 2.0 * sqrt(10.0) * (x[3] - x[0]);
		/********************************/
	}
}

void program3_2(void)
{
	char rdFile[256];
	char wrFile[256];

	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.0, 0.0, 0.0, 0.0 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;
	double ans = 0.0;

	sprintf(wrFile, "roots_found_3-2.txt");
	printf("\n\n>>> Program3_2 Program <<<\n");
	FILE* fp_w = fopen(wrFile, "w");
	if (fp_w == NULL)
	{
		printf("%s file open error...\n", wrFile);
		return;
	}

	x[0] = 0.9, x[1] = -0.9, x[2] = 1.25, x[3] = -1.25;
	printf("initial root : x1 = %lf, x2 =  %lf, x3 =  %lf, x4 = %lf\n", x[0], x[1], x[2], x[3]);
	fprintf(fp_w, "initial root : x1 = %lf, x2 =  %lf, x3 =  %lf, x4 = %lf\n", x[0], x[1], x[2], x[3]);
	hybrj1_(f3_2, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

	printf("x1 = %lf, x2 =  %lf, x3 =  %lf, x4 = %lf\n", x[0], x[1], x[2], x[3]);
	printf("info is %d\n", info);

	fprintf(fp_w, "x1 = %lf, x2 =  %lf, x3 =  %lf, x4 = %lf\n", x[0], x[1], x[2], x[3]);
	fprintf(fp_w, "info is %d\n", info);

	ans = x[0] + 10.0 * x[1] + 9.0;
	fprintf(fp_w, "|f1(x1, x2, x3, x4)| = %lf\n", fabs(ans));
	printf("|f1(x[0], x[1], x[2], x[3])| = %lf\n", fabs(ans));

	ans = sqrt(5.0) * (x[3] - x[2]) - 2.0 * sqrt(5.0);
	fprintf(fp_w, "|f2(x1, x2, x3, x4)| = %lf\n", fabs(ans));
	printf("|f2(x1, x2, x3, x4)| = %lf\n", fabs(ans));

	ans = (x[1] - 2.0 * x[2]) * (x[1] - 2.0 * x[2]) - 9.0;
	fprintf(fp_w, "|f3(x1, x2, x3, x4)| = %lf\n", fabs(ans));
	printf("|f3(x1, x2, x3, x4)| = %lf\n", fabs(ans));

	ans = sqrt(10.0) * (x[0] - x[3]) * (x[0] - x[3]) - 2.0 * sqrt(10.0);
	fprintf(fp_w, "|f4(x1, x2, x3, x4)| = %lf\n", fabs(ans));
	printf("|f4(x1, x2, x3, x4)| = %lf\n", fabs(ans));
}
