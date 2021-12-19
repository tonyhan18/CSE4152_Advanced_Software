#include "my_solver.h"

void program2_1(void)
{
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/
	int size, n;
	int min = 0, max = 0;
	int i, j;
	double h, nh;
	double* x;
	double* y;
	double* nx;
	double* ny;
	double min_x = 0;
	double max_x = 0;
	double sum = 0, sum_y = 0, check_sum = 0;
	

	fscanf(fp_r, "%d %lf", &size, &h);
	x = (double*)malloc(sizeof(double) * size);
	y = (double*)malloc(sizeof(double) * size);
	nx = (double*)malloc(sizeof(double) * size);
	ny = (double*)malloc(sizeof(double) * size);

	for (i = 0; i < size; ++i)
	{
		fscanf(fp_r, "%lf %lf", &x[i], &y[i]);
	}

	min_x = x[0];
	max_x = x[size - 1];

	// normalization of x
	for (i = 0; i < size; ++i)
	{
		nx[i] = (double)(x[i] - min_x) / (max_x - min_x);
	}

	// division quadrature
	for (i = 0; i < size; ++i)
	{
		if (i + 1 == size)
		{
			break;
		}
		sum += (nx[1] - nx[0]) / 2 * (y[i] + y[i + 1]);
	}

	for (i = 0; i < size; ++i)
	{
		ny[i] = y[i] / sum;
	}
	nh = 1 / (double)(size - 1);

	fprintf(fp_w, "%d %lf\n", size, nh);
	for (i = 0; i < size; ++i)
	{
		fprintf(fp_w, "%lf %lf\n", (double)nx[i], (double)ny[i]);
	}

	sum = 0;
	for (i = 0; i < size; ++i)
	{
		if (i + 1 == size)
		{
			break;
		}
		sum += (nx[1] - nx[0]) / 2 * (ny[i + 1] + ny[i]);
	}
	printf("*** integrating the pdf from 0.0 to 1.0 = %.6f\n", sum);
	
	for (i = 0; i < size; ++i)
	{
		if (nx[i] >= 0.25)
		{
			break;
		}
		max = i;
	}


	// ��ٸ��� ����
	sum = 0;
	for (int i = 0; i < max + 1; ++i)
	{
		if (i + 1 == max + 1)\
		{
			break;
		}
		sum += (nx[1] - nx[0]) / 2 * (ny[i + 1] + ny[i]);
	}

	///////////////////// ������ ���� /////////////////////
	// �� �κ� ���� ���ϱ�
	sum += (ny[max] + (ny[max + 1] - ny[max]) / (nx[max + 1] - nx[max]) * (0.25 - nx[max] / 2)) * (0.25 - nx[max]);

	printf("*** integrating the pdf from 0.0 to 0.25 = %.6f\n", sum);

	sum = 0;
	for (i = 0; i < size; ++i)
	{
		if (0.25 <= nx[i])
		{
			min = i;
			break;
		}
	}

	for (i = 0; i < size; i++)
	{
		if (0.5 <= nx[i])
		{
			break;
		}
		max = i;
	}

	// min~max ��ٸ���
	for (int i = min; i < max + 1; ++i)
	{
		if (i + 1 == max + 1)
		{
			break;
		}
		sum += (nx[1] - nx[0]) / 2 * (ny[i + 1] + ny[i]);
	}

	// front
	sum += (ny[min] + (ny[min + 1] - ny[min]) / (nx[min + 1] - nx[min]) * (0.25 - nx[min] / 2)) * (0.25 - nx[min]);
	// back
	sum += (ny[max] + (ny[max + 1] - ny[max]) / (nx[max + 1] - nx[max]) * (0.5 - nx[max] / 2)) * (0.5 - nx[max]);
	printf("*** integrating the pdf from 0.25 to 0.5 = %.6f\n", sum);

	for (i = 0; i < size; ++i)
	{
		if (0.5 <= nx[i])
		{
			min = i;
			break;
		}
	}

	for (i = 0; i < size; ++i)
	{
		if (0.75 <= nx[i])
		{
			break;
		}
		max = i;
	}

	// min~max ��ٸ���
	sum = 0;
	for (int i = min; i < max + 1; ++i)
	{
		if (i + 1 == max + 1)
		{
			break;
		}
		sum += (nx[1] - nx[0]) / 2 * (ny[i + 1] + ny[i]);
	}

	// front
	sum += (ny[min] + (ny[min + 1] - ny[min]) / (nx[min + 1] - nx[min]) * (0.5 - nx[min] / 2)) * (0.5 - nx[min]);
	// back
	sum += (ny[max] + (ny[max + 1] - ny[max]) / (nx[max + 1] - nx[max]) * (0.75 - nx[max] / 2)) * (0.75 - nx[max]);

	printf("*** integrating the pdf from 0.5 to 0.75 = %.6f\n", sum);

	sum = 0;
	for (i = 0; i < size; ++i)
	{
		if (0.75 <= nx[i])
		{
			min = i;
			break;
		}
	}

	// min~1 ��ٸ���
	for (int i = min; i < size; ++i)
	{
		if (i + 1 == size)
		{
			break;
		}
		sum += (nx[1] - nx[0]) / 2 * (ny[i + 1] + ny[i]);
	}

	// front
	sum += (ny[min] + (ny[min + 1] - ny[min]) / (nx[min + 1] - nx[min]) * (0.75 - nx[min] / 2)) * (0.75 - nx[min]);
	printf("*** integrating the pdf from 0.75 to 1.0 = %.6f\n", sum);

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
