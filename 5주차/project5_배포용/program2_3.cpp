#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

// HOMEWORK 2-1
void function2_1()
{
	int size;
	double avg = 0, avg_sum = 0, devi = 0, devi_sum = 0;
	double* U, * xA, * xB, * xC, tmp;
	double var = 0, iseed;
	double ramA, ramB, ramC;

	srand(time(NULL));
	printf("생성할 지수 분포의 난수 개수를 입력하시오 : ");
	scanf("%d", &size);
	U = (double*)malloc(sizeof(double) * size);
	xA = (double*)malloc(sizeof(double) * size);
	xB = (double*)malloc(sizeof(double) * size);
	xC = (double*)malloc(sizeof(double) * size);

	// Generate random numbers between 0 and 1
	for (int i = 0; i < size; i++) {
		iseed = (double)rand() / (RAND_MAX + 1);
		U[i] = iseed;
	}

	// Allocate three different ramda values which i choosed
	ramA = 0.5;
	ramB = 1.0;
	ramC = 1.5;

	// Calculate X that follows each exponential distribution
	for (int i = 0; i < size; i++) {
		xA[i] = -(log(1 - U[i]) / ramA);
		xB[i] = -(log(1 - U[i]) / ramB);
		xC[i] = -(log(1 - U[i]) / ramC);
	}

	// Calculate the avg and variance for comparing with theratical values
	for (int i = 0; i < size; i++) {
		avg_sum += xA[i];
	}
	avg = avg_sum / (double)size;

	for (int i = 0; i < size; i++) {
		devi = xA[i] - avg;
		devi_sum += devi * devi;
	}

	var = devi_sum / (double)size;
	printf("---------------------------------------------------------------------------\n");
	printf("-				ramda A result			  -\n");
	printf("---------------------------------------------------------------------------\n");
	printf("ram = %lf		1/ram = %6.6lf		1/ram^2 = %6.6lf\n", ramA, 1 / ramA, 1 / (ramA * ramA));
	printf("			E[X]= %6.6lf			Var[X]=%6.6lf\n", avg, var);
	printf("---------------------------------------------------------------------------\n");

	avg_sum = 0;
	devi_sum = 0;

	// ramb
	for (int i = 0; i < size; i++) {
		avg_sum += xB[i];
	}
	avg = avg_sum / (double)size;

	for (int i = 0; i < size; i++) {
		devi = xB[i] - avg;
		devi_sum += devi * devi;
	}

	var = devi_sum / (double)size;
	printf("-				ramda B result			  -\n");
	printf("---------------------------------------------------------------------------\n");
	printf("ram = %lf		1/ram = %6.6lf		1/ram^2 = %6.6lf\n", ramB, 1 / ramB, 1 / (ramB * ramB));
	printf("			E[X]= %6.6lf			Var[X]=%6.6lf\n", avg, var);
	printf("---------------------------------------------------------------------------\n");
	avg_sum = 0;
	devi_sum = 0;

	// Rmada_c
	for (int i = 0; i < size; i++) {
		avg_sum += xC[i];
	}
	avg = avg_sum / (double)size;

	for (int i = 0; i < size; i++) {
		devi = xC[i] - avg;
		devi_sum += devi * devi;
	}

	var = devi_sum / (double)size;
	printf("-				ramda C result			  -\n");
	printf("---------------------------------------------------------------------------\n");
	printf("ram = %lf		1/ram = %6.6lf		1/ram^2 = %6.6lf\n", ramC, 1 / ramC, 1 / (ramC * ramC));
	printf("			E[X]= %6.6lf			Var[X]=%6.6lf\n", avg, var);
	printf("---------------------------------------------------------------------------\n");

	free(U);
	free(xA);
	free(xB);
	free(xC);
}

// HOMEWORK
void program2_3()
{
	FILE* fp_r1, * fp_r2, * fp_w;

	fp_r1 = fopen("pdf_table.txt", "r");
	fp_r2 = fopen("random_event_table.txt", "r");
	fp_w = fopen("histogram.txt", "w");

	// variables for reading
	int size_r, size;
	int cur = 0, xr_cnt = 0;
	double h;
	double* x, * y, * xr, tmp;
	double sect_pnt, sect_inter;
	
	

	fscanf(fp_r1, "%d %lf", &size, &h);

	x = (double*)malloc(sizeof(double) * size);
	y = (double*)malloc(sizeof(double) * size);

	for (int i = 0; i < size; i++) {
		fscanf(fp_r1, "%lf %lf", &x[i], &y[i]);
	}

	fscanf(fp_r2, "%d", &size_r);

	xr = (double*)malloc(sizeof(double) * size_r);

	for (int i = 0; i < size_r; i++) {
		fscanf(fp_r2, "%lf", &xr[i]);
	}

	// sort the xr
	for (int i = 0; i < size_r; i++) {
		for (int j = 0; j < size_r - i - 1; j++) {
			if (xr[j + 1] < xr[j]) {
				tmp = xr[j];
				xr[j] = xr[j + 1];
				xr[j + 1] = tmp;
			}
		}
	}
	sect_inter = 1 / (double)500;
	sect_pnt = x[0];

	for (int i = 0; i < 500; i++) {

		while (1) {
			if (sect_pnt > xr[cur] || xr[cur] > sect_pnt + sect_inter || cur >= size_r) {
				break;
			}
			xr_cnt++;
			cur++;
		}
		fprintf(fp_w, "Section[%.15lf-%.15lf]: The number of random numbers is %d, The probability is %.15f\n", sect_pnt, sect_pnt + sect_inter, xr_cnt, (double)xr_cnt / size_r);
		sect_pnt += sect_inter;
		xr_cnt = 0;
	}

	free(x);
	free(y);
	free(xr);

	if (fp_r1 != NULL) fclose(fp_r1);
	if (fp_r2 != NULL) fclose(fp_r2);
	if (fp_w != NULL) fclose(fp_w);

	// HOMEWORK 2-1
	function2_1();

	program2_2_a();
	program2_2_b();
}

// HOMEWORK

double _f(double xn,  double* x, double* y, int n, double seed) {
	double sum = 0;
	int max = 0;

	for (int i = 0; i < n; i++) {
		if (xn <= x[i]) break;
		max = i;
	}

	// 0~max size
	for (int i = 0; i < max + 1; i++) {
		if (i + 1 == max + 1) break;
		sum += (x[1] - x[0]) * (y[i + 1] + y[i]) / 2;
	}

	// others
	sum += (y[max] + (y[max + 1] - y[max]) / (x[max + 1] - x[max]) * (xn - x[max]) / 2.0) * (xn - x[max]) - seed;
	return (sum);
}

double _fp(double xn, double* x, double* y, int n, double seed) {

	double s;
	int idx = 0;


	for (int i = 0; i < n; i++) {
		if (xn <= x[i]) break;
		idx = i;
	}

	s = (xn - x[idx]) / (x[idx + 1] - x[idx]);
	return ((1 - s) * y[idx] + s * y[idx + 1]);
}


void program2_2_a()
{
	int i = 0, j = 0;
	int size;
	int len;
	double* y, * x, * xn_res;
	double iseed;
	double xn, an, bn, h;

	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");


	srand(time(NULL));
	fscanf(fp_r, "%d %lf", &len, &h);

	x = (double*)malloc(sizeof(double) * len);
	y = (double*)malloc(sizeof(double) * len);


	for (i = 0; i < len; i++) {
		fscanf(fp_r, "%lf %lf", &x[i], &y[i]);
	}

	size = 1000;
	fprintf(fp_w, "%d\n", size);
	xn_res = (double*)malloc(sizeof(double) * size);

	__int64 start, freq, end;
	float resultTime = 0;

	CHECK_TIME_START;


	/***************************************************/
	// something to do...

	// Bisection Method
	for (i = 0; i < size; i++) {
		j = 0;
		iseed = (double)rand() / (RAND_MAX + 1);
		an = 0;
		bn = 1;
		

		while (1) {
			xn = (an + bn) / 2.0;

			if (_f(xn, x, y, len, iseed) == 0) {
				xn_res[i] = xn;
				break;
			}

			if (j >= Nmax || fabs(_f(xn, x, y, len, iseed)) < DELTA || (fabs(bn - an) < EPSILON)) {
				xn_res[i] = xn;
				break;
			}

			if (_f(an, x, y, len, iseed) * _f(xn, x, y, len, iseed) < 0) {
				bn = xn;
			}
			else {
				an = xn;
			}

			j++;
		}
	}

	/***************************************************/


	CHECK_TIME_END(resultTime);

	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);

	for (int i = 0; i < size; i++) {
		fprintf(fp_w, "%.15lf\n", xn_res[i]);
	}

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	free(xn_res);
	free(x);
	free(y);
}

void program2_2_b()
{
	int size;
	int i = 0, j = 0;
	int len;
	double h;
	double* y, * x;
	double iseed;
	double xn, xn1, xn2, an, bn, an1, bn1, cn;
	double* xn_res;

	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	srand(time(NULL));
	fscanf(fp_r, "%d %lf", &len, &h);

	x = (double*)malloc(sizeof(double) * len);
	y = (double*)malloc(sizeof(double) * len);


	for (i = 0; i < len; i++) {
		fscanf(fp_r, "%lf %lf", &x[i], &y[i]);
	}

	size = 1000;
	fprintf(fp_w, "%d\n", size);
	xn_res = (double*)malloc(sizeof(double) * size);

	__int64 start, freq, end;
	float resultTime = 0;

	CHECK_TIME_START;

	// something to do...

	for (i = 0; i < size; i++) {
		iseed = (double)rand() / (RAND_MAX + 1);

		// Getting x1 and x0 by using Bisection Method
		an = 0.0;
		bn = 1.0;
		for (int i = 0; i < 5; i++) {
			cn = (an + bn) / 2.0;
			if (_f(an, x, y, len, iseed) * _f(cn, x, y, len, iseed) < 0) {
				bn = cn;
			}
			else {
				an = cn;
			}
		}

		// Secant Method
		xn2 = an; // xn-1
		xn = bn; // xn
		j = 0;

		while (1) {
			// xn+1
			xn1 = xn - _f(xn,  x, y, len, iseed) * (xn - xn2) / (_f(xn, x, y, len, iseed) - _f(xn2, x, y, len, iseed));

			if (j >= Nmax || fabs(_f(xn1, x, y, len, iseed)) < DELTA || (fabs(xn1 - xn) < EPSILON)) {
				xn_res[i] = xn1;
				break;
			}

			xn2 = xn;
			xn = xn1;
			j++;
		}
	}

	CHECK_TIME_END(resultTime);

	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);

	for (int i = 0; i < size; i++) {
		fprintf(fp_w, "%.15lf\n", xn_res[i]);
	}

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);


	free(x);
	free(y);
	free(xn_res);

}

