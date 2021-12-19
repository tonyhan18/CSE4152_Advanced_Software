#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

double fx(double xn, double* x, double* y, int size, double seed)
{
	double sum = 0;
	int max = 0;
	int i;

	for (i = 0; i < size; ++i)
	{
		if (xn <= x[i]) break;
		max = i;
	}
	// 0 to max trapezoid
	for (i = 0; i < max; ++i)
	{
		if (i == max + 1) break;
		sum += (x[1] - x[0]) * (y[i + 1] + y[i]) / 2.0;
	}
	// other part
	sum += (y[i + 1] + (y[i + 1] - y[i]) / (x[i + 1] - x[i]) * (xn - x[i]) / 2.0) * (xn - x[i]) - seed;
	return (sum);
}
void program2_2()
{
	FILE* fp_r, *fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/
	int size;
	double h;
	double* x, * y;
	int nr;
	double an, bn, xn;
	bool flag = false;
	int j = 0;

	fscanf(fp_r, "%d %lf", &size, &h);
	x = (double*)malloc(sizeof(double) * size);
	y = (double*)malloc(sizeof(double) * size);
	for (int i = 0; i < size; ++i)
	{
		fscanf(fp_r, "%lf %lf", &x[i], &y[i]);
	}

	printf("난수 개수 nr을 입력하시오 : ");
	scanf("%d", &nr);

	fprintf(fp_w, "%d\n", nr);
	srand(time(NULL));

	for (int i = 0; i < nr; ++i)
	{
		an = 0;
		bn = 1;
		j = 0;
		double irand = (double)rand() / (RAND_MAX + 1);

		while (1)
		{
			xn = (an + bn) / 2.0;
			if (fx(xn, x, y, size, irand) == 0)
			{
				fprintf(fp_w, "%.15f\n", xn);
				break;
			}
			if (j >= Nmax || fabs(fx(xn, x, y, size, irand)) < DELTA || fabs(bn - an) < EPSILON)
			{
				fprintf(fp_w, "%.15f\n", xn);
				break;
			}
			if (fx(an, x, y, size, irand) * fx(xn, x, y, size, irand) < 0)
			{
				bn = xn;
			}
			else
			{
				an = xn;
			}
			j++;
		}
	}


	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
