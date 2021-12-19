#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection Method -- HOMEWORK
**********************************************/
void program1_3(FILE *fp)
{
	double a0, b0, x0, x1 , temp;
	int n;

	
	printf("========================================\n");
	printf("=           Bisection Method           =\n");
	printf("========================================\n");
	/*fprintf(fp, "========================================\n");
	fprintf(fp, "=           Bisection Method           =\n");
	fprintf(fp, "========================================\n");*/
	printf("초기 구간의 경계값 a0를 입력하시오 :");
	scanf("%lf", &a0);
	printf("초기 구간의 경계값 b0를 입력하시오 :");
	scanf("%lf", &b0);
	
	fprintf(fp,"%lf", &a0);
	fprintf(fp,"%lf", &b0);
	printf("%3s%16s%24s%24s%24s\n", "i", "a0", "b0", "temp", "|f(xn1)|");
	fprintf(fp,"%3s%16s%24s%24s%24s\n", "i", "a0", "b0", "temp", "|f(xn1)|");

	n = 0;
	while (n <= Nmax)
	{
		temp = (a0 + b0) / 2.0;

		// if find answer
		if (_f(temp) == 0)
		{
			printf("%3d%25.16e%25.16e%25.16e%13.4e\n", n, a0, b0, temp, fabs(temp));
			fprintf(fp,"%3d%25.16e%25.16e%25.16e%13.4e\n", n, a0, b0, temp, fabs(temp));
			break;
		}

		if (fabs(_f(temp)) < DELTA || fabs(b0 - a0) < EPSILON)
		{
			printf("%3d%25.16e%25.16e%25.16e%13.4e\n", n, a0, b0, temp, fabs(temp));
			fprintf(fp, "%3d%25.16e%25.16e%25.16e%13.4e\n", n, a0, b0, temp, fabs(temp));
			break;
		}

		printf("%3d%25.16e%25.16e%25.16e%13.4e\n", n, a0, b0, temp, fabs(temp));
		fprintf(fp, "%3d%25.16e%25.16e%25.16e%13.4e\n", n, a0, b0, temp, fabs(temp));
		n++;
		if (_f(a0) * _f(temp) < 0)
		{
			b0 = temp;
		}
		else
		{
			a0 = temp;
		}
	}
}