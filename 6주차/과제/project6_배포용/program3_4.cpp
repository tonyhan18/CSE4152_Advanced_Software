#include "my_solver.h"
#define index_2d(row, col, dim) row*dim+col
#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void program3_4(void)
{
	char rdfile[256];
	char wrfile[256];
	sprintf(rdfile, "linear_system_3-4.txt");
	sprintf(wrfile, "solution_3-4.txt");

	printf("\n\n>>> Program3_4 Program <<<\n");
	FILE* fp_r = fopen(rdfile, "r");
	if (fp_r == NULL)
	{
		printf("%s file open error...\n", rdfile);
		return ;
	}
	FILE* fp_w = fopen(wrfile, "w");
	if (fp_w == NULL)
	{
		printf("%s file open error...\n", wrfile);
		return ;
	}

	int ia, n, *l;
	float *a, *b, *x, *y;

	fscanf(fp_r, "%d", &n);
	fprintf(fp_w, "%d\n", n);
	ia = n;
	l = (int*)malloc(sizeof(int) * n);

	a = (float*)malloc(sizeof(float) * n * n);
	b = (float*)malloc(sizeof(float) * n);
	x = (float*)malloc(sizeof(float) * n);
	y = (float*)malloc(sizeof(float) * n);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			fscanf(fp_r, "%f", &a[index_2d(i, j, n)]);
		}
	}
	for (int i = 0; i < n; ++i)
	{
		fscanf(fp_r, "%f", &b[i]);
	}
	gespp_(&n, a, &ia, l, y);
	solve_(&n, a, &ia, l, b, x);

	printf("***** Solution *****\n");
	float test = 0.0;
	for (int i = 0; i < n; ++i)
	{
		printf("x%d = %.6f\n", i, x[i]);
		fprintf(fp_w, "%.6f\n", x[i]);
	}

	float sum = 0.0, pow = 0.0, pow2 = 0.0, ans = 0.0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sum += a[index_2d(i, j, n)] * x[j];
		}
		sum -= b[i];
		pow += sum * sum;
		sum = 0.0;
	}
	for (int i = 0; i < n; ++i)
	{
		pow2 += b[i] * b[i];
	}

	ans = sqrt(pow) / sqrt(pow2);

	printf("%.6f\n", ans);
	fprintf(fp_w, "%.6f\n", ans);
}
