#include "my_solver.h"

void program2_1()
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
	int size;
	double h;
	double* x, * y;
	double minX, maxX;
	double* normX, * normY;
	double sum = 0;
	double normH;
	int min = 0, max = 0;

	fscanf(fp_r, "%d %lf", &size, &h);
	x = (double*)malloc(sizeof(double) * size);
	y = (double*)malloc(sizeof(double) * size);
	normX = (double*)malloc(sizeof(double) * size);
	normY = (double*)malloc(sizeof(double) * size);

	//////////////// get size of pdf ////////////////
	// read Data
	for (int i = 0; i < size; ++i)
	{
		fscanf(fp_r, "%lf %lf", &x[i], &y[i]);
	}
	minX = x[0];
	maxX = x[size - 1];

	// normalize X
	for (int i = 0; i < size; ++i)
	{
		normX[i] = (double)(x[i] - minX) / (maxX - minX);
	}
	// division quadrature - to norm height
	for (int i = 0; i < size; ++i)
	{
		if (i + 1 == size) break;
		sum += (normX[i + 1] - normX[i]) * (y[i] + y[i + 1]) / 2.0;
	}
	// normalize Y
	for (int i = 0; i < size; ++i)
	{
		normY[i] = y[i] / sum;
	}
	normH = 1 / (double)(size - 1);

	// Write all the data
	fprintf(fp_w, "%d %lf\n", size, normH);
	for (int i = 0; i < size; ++i)
	{
		fprintf(fp_w, "%lf %lf\n", (double)normX[i], (double)normY[i]);
	}
	// division quadrature - to real pdf size
	sum = 0;
	for(int i = 0 ; i < size ; ++i)
	{
		if (i + 1 == size) break;
		sum += (normX[i + 1] - normX[i]) * (normY[i + 1] + normY[i]) / 2.0;
	}
	printf("*** Integration the pdf from 0.0 to 1.0 = %.6lf\n", sum);

	//////////////// get size of pdf splited ////////////////

	// division quadrature - 0 to 0.25
	for (int i = 0; i < size; ++i)
	{
		if (normX[i] >= 0.25) break;
		max = i;
	}
	
	sum = 0;
	for (int i = 0; i < max + 1; ++i)
	{
		if (i + 1 == max + 1) break;
		sum += (normX[1] - normX[0]) * (normY[i + 1] + normY[i]) / 2.0;
	}
	sum += (normY[max] + (normY[max + 1] - normY[max]) / (normX[max + 1] - normX[max]) * (0.25 - normX[max] / 2.0))* (0.25 - normX[max]);
	printf("*** Integration the pdf from 0.0 to 0.25 = %.6lf\n", sum);

	// division quadrature - 0.25 to 0.5
	sum = 0;
	for (int i = 0; i < size; ++i)
	{
		if (0.25 <= normX[i])
		{
			min = i;
			break;
		}
	}
	for (int i = 0; i < size; ++i)
	{
		if (0.5 <= normX[i])
		{
			max = i;
			break;
		}
	}
	for (int i = min; i < max + 1; ++i)
	{
		if (i + 1 == max + 1) break;
		sum += (normX[1] - normX[0]) * (normY[i + 1] + normY[i]) / 2.0;
	}
	sum += (normY[min] + (normY[min + 1] - normY[min]) / (normX[min + 1] - normX[min]) * (0.25 - normX[min] / 2.0)) * (0.25 - normX[min]);
	sum += (normY[max] + (normY[max + 1] - normY[max]) / (normX[max + 1] - normX[max]) * (0.25 - normX[max] / 2.0)) * (0.5 - normX[max]);
	printf("*** Integration the pdf from 0.25 to 0.5 = %.6lf\n", sum);


	// division quadrature - 0.5 to 0.75
	sum = 0;
	for (int i = 0; i < size; ++i)
	{
		if (0.5 <= normX[i])
		{
			min = i;
			break;
		}
	}
	for (int i = 0; i < size; ++i)
	{
		if (0.75 <= normX[i])
		{
			max = i;
			break;
		}
	}
	for (int i = min; i < max + 1; ++i)
	{
		if (i + 1 == max + 1) break;
		sum += (normX[1] - normX[0]) * (normY[i + 1] + normY[i]) / 2.0;
	}
	sum += (normY[min] + (normY[min + 1] - normY[min]) / (normX[min + 1] - normX[min]) * (0.5 - normX[min] / 2.0)) * (0.5 - normX[min]);
	sum += (normY[max] + (normY[max + 1] - normY[max]) / (normX[max + 1] - normX[max]) * (0.75 - normX[max] / 2.0)) * (0.75 - normX[max]);
	printf("*** Integration the pdf from 0.5 to 0.75 = %.6lf\n", sum);

	// division quadrature - 0.75 to 1.0
	sum = 0;
	for (int i = 0; i < size; ++i)
	{
		if (0.75 <= normX[i])
		{
			min = i;
			break;
		}
	}
	for (int i = min; i < size; ++i)
	{
		if (i + 1 == size) break;
		sum += (normX[1] - normX[0]) * (normY[i + 1] + normY[i]) / 2.0;
	}
	sum += (normY[min] + (normY[min + 1] - normY[min]) / (normX[min + 1] - normX[min]) * (0.75 - normX[min] / 2.0)) * (0.75 - normX[min]);
	printf("*** Integration the pdf from 0.75 to 1.0 = %.6lf\n", sum);

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
