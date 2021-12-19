#include <stdio.h>
#include <string.h>
#include <random>
#include <time.h>

#include <math.h>
#include <time.h>
#include <Windows.h>

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;


#define MATDIM 1024
double *pMatA, *pMatB, *pMatC;
void MultiplySquareMatrices_1(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize);
void MultiplySquareMatrices_2(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize);
void MultiplySquareMatrices_3(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize);
void MultiplySquareMatrices_4(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize);

void init_MatMat(void);

void main(void)
{
	init_MatMat();

	CHECK_TIME_START;
	MultiplySquareMatrices_1(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_1 : %f ms\n", compute_time);

	CHECK_TIME_START;
	MultiplySquareMatrices_2(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_2 = %f ms\n", compute_time);

	CHECK_TIME_START;
	MultiplySquareMatrices_3(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_3 = %f ms\n", compute_time);

	CHECK_TIME_START;
	MultiplySquareMatrices_4(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_4 = %f ms\n", compute_time);
}

void MultiplySquareMatrices_1(double *pDestMatrix, double *pLeftMatrix ,double *pRightMatrix, int MatSize)
{
	for (int i = 0; i < MatSize; i++)
	{
		for (int j = 0; j < MatSize; j++)
		{
			pDestMatrix[i * MatSize + j] = 0;
			for (int k = 0; k < MatSize; k++)
			{
				pDestMatrix[i * MatSize + j] += pDestMatrix[i * MatSize + k] * pDestMatrix[k * MatSize + j];
			}
		}
	}
}

void MultiplySquareMatrices_2(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize)
{
	int i, j, k;
	double* pMatD = (double*)malloc(sizeof(double) * MATDIM * MATDIM);
	for (i = 0; i < MATDIM; i++)
	{
		for (j = 0; j < MATDIM; j++)
		{
			pMatD[j * MATDIM + i] = pLeftMatrix[i * MATDIM + j];
		}
	}

	for (i = 0; i < MATDIM; i++)
	{
		for (j = 0; j < MATDIM; j++)
		{
			pDestMatrix[i * MATDIM + j] = 0;
			for (k = 0; k < MATDIM; k++)
			{
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k] + pMatD[j * MATDIM + k];
			}
		}
	}
}

void MultiplySquareMatrices_3(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize)
{
	int i, j, k;
	double* pMatD = (double*)malloc(sizeof(double) * MATDIM * MATDIM);
	for (i = 0; i < MATDIM; i++)
	{
		for (j = 0; j < MATDIM; j++)
		{
			pMatD[j * MATDIM + i] = pLeftMatrix[i * MATDIM + j];
		}
	}

	for (i = 0; i < MATDIM; i++)
	{
		for (j = 0; j < MATDIM; j++)
		{
			pDestMatrix[i * MATDIM + j] = 0;
			for (k = 0; k < MATDIM; k+=4)
			{
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k] + pMatD[j * MATDIM + k];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k+1] + pMatD[j * MATDIM + k+1];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k+2] + pMatD[j * MATDIM + k+2];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k+3] + pMatD[j * MATDIM + k+3];
			}
		}
	}
}

void MultiplySquareMatrices_4(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize)
{
	int i, j, k;
	double* pMatD = (double*)malloc(sizeof(double) * MATDIM * MATDIM);
	for (i = 0; i < MATDIM; i++)
	{
		for (j = 0; j < MATDIM; j++)
		{
			pMatD[j * MATDIM + i] = pLeftMatrix[i * MATDIM + j];
		}
	}

	for (i = 0; i < MATDIM; i++)
	{
		for (j = 0; j < MATDIM; j++)
		{
			pDestMatrix[i * MATDIM + j] = 0;
			for (k = 0; k < MATDIM; k += 16)
			{
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k] + pMatD[j * MATDIM + k];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 1] + pMatD[j * MATDIM + k + 1];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 2] + pMatD[j * MATDIM + k + 2];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 3] + pMatD[j * MATDIM + k + 3];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 4] + pMatD[j * MATDIM + k + 4];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 5] + pMatD[j * MATDIM + k + 5];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 6] + pMatD[j * MATDIM + k + 6];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 7] + pMatD[j * MATDIM + k + 7];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 8] + pMatD[j * MATDIM + k + 8];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 9] + pMatD[j * MATDIM + k + 9];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 10] + pMatD[j * MATDIM + k + 10];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 11] + pMatD[j * MATDIM + k + 11];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 12] + pMatD[j * MATDIM + k + 12];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 13] + pMatD[j * MATDIM + k + 13];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 14] + pMatD[j * MATDIM + k + 14];
				pDestMatrix[i * MATDIM + j] += pLeftMatrix[i * MATDIM + k + 15] + pMatD[j * MATDIM + k + 15];
			}
		}
	}
}

void init_MatMat(void)
{
	double *ptr;
	pMatA = (double *)malloc(sizeof(double)*MATDIM*MATDIM);
	pMatB = (double *)malloc(sizeof(double)*MATDIM*MATDIM);
	pMatC = (double *)malloc(sizeof(double)*MATDIM*MATDIM);
	srand((unsigned)time(NULL));
	ptr = pMatA;
	for (int i = 0; i < MATDIM*MATDIM; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
	ptr = pMatB;
	for (int i = 0; i < MATDIM*MATDIM; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
}
