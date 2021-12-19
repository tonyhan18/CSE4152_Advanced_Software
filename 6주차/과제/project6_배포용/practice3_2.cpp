#include "my_solver.h"

void square(double *a, double *b, double c, double d)
{
	double real = *a * c - *b * d;
	double comp = *a * d + *b * c;
	*a = real;
	*b = comp;
}
void practice3_2() {
	char readfile[256];
	char writefile[256];

	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;

	printf("\n\n>>> Practice3_2 Program <<<\n");
	for (int t = 1; t <= 6; t++) {

		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		fscanf(fp_r, "%d", &DEGREE);
		fprintf(fp_w, "DRGREE = %d\n", DEGREE);
		NCOEF = DEGREE + 1;

		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);


		/********************************/
		printf("times = %d | DEGREE = %d\n", t, DEGREE);
		for (i = 0; i < NCOEF; ++i)
		{
			fscanf(fp_r, "%lf", &poly[i]);
		}
		double ans = 0.0;
		int degree = DEGREE;
		long fail;
		rpoly_(poly, &degree, zeror, zeroi, &fail);

		if (fail)
		{
			printf("wrong\n\n");
			fprintf(fp_w, "wrong\n\n");
			free(zeroi);
			free(zeror);
			free(poly);

			if (fp_r != NULL) fclose(fp_r);
			if (fp_w != NULL) fclose(fp_w);
			continue;
		}
		printf("\n");
		fprintf(fp_w, "\n");
		for (i = 0; i < degree; ++i)
		{
			printf("zeror[%d] =%10f	", i, zeror[i]);
			fprintf(fp_w, "zeror[%d] =%10f	", i, zeror[i]);
			printf("zeroi[%d] =%10f	", i, zeroi[i]);
			fprintf(fp_w,"zeroi[%d] =%10f	", i, zeroi[i]);
			// real number
			double realRes = 0;
			double compRes = 0;
			for (int j = 0; j < DEGREE; ++j)
			{
				double realMid = zeror[i];
				double compMid = zeroi[i];

				for (int k = DEGREE - j; k > 1; k--)
				{
					square(&realMid, &compMid, zeror[i], zeroi[i]);
				}
				realMid *= poly[j];
				compMid *= poly[j];

				realRes += realMid;
				compRes += compMid;
			}
			realRes += poly[NCOEF - 1];
			printf("|f(x*)| = %lf + %lf * i\n", fabs(realRes), fabs(compRes));
			fprintf(fp_w, "|f(x*)| = %lf + %lf * i\n", fabs(realRes), fabs(compRes));
		}
		printf("\n\n");
		fprintf(fp_w,"\n\n");
		/********************************/


		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
}