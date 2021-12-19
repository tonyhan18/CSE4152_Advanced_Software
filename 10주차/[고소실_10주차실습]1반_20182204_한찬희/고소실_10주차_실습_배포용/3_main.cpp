#include <stdio.h>
#include <random>
#include <time.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#define N 50
double Taylor_series(double x, int n);
double Taylor_series_ex(double x, int n);
__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

void main(void)
{
	printf("*** f<-8.3> = %.6e \n", Taylor_series(-8.3, N));
	printf("*** f<-8.3> = %.6e \n", Taylor_series_ex(-8.3, N));
	printf("*** f<-8.3> = %.6e \n", pow(2.71828182846, -8.3));
}

double Taylor_series(double x, int n)
{
	float ans = 0.0;
	int i, j;
	float div = 1.0;
	for (i = 0; i < n; i++)
	{
		div = 1.0;
		for (j = i; j > 0; j--)
		{
			div *= j;
		}
		ans += (pow(x, i)) / div;
	}
	return (ans);
}


double Taylor_series_ex(double x, int n)
{
	double ans = 1.0;
	int i, j;

	for (i = n - 1; i > 0; i--)
	{
		ans *= (double)(x) / i;
		ans += 1.0;
	}
	return (ans);
}
