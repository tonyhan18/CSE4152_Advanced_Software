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
float compute_time1, compute_time2;


#define TWO_23 10000
#define MATDIM 1024
#define HW1_N 1000
float *hw1_x, hw1_E, hw1_var1, hw1_var2;
float hw2_a, hw2_b, hw2_c, hw2_naive_ans[2], hw2_pre_ans[2];

/* hw1 */
void init_hw1(int fixed);
void hw1_calc_e();
void hw1_calc_var1();
void hw1_calc_var2();
/* hw2 */
void hw2_naive();
void hw2_safe();
float hw2_verify(float x);
/* hw3 */


void main(void)
{
	srand((unsigned)time(NULL));

	/* hw1 */
	int d = 1;
	puts("====== hw1 ======");
	init_hw1(d);
	printf("init_hw1(%d), HW1_N = %d\n", d, HW1_N);
	CHECK_TIME_START;
	hw1_calc_var1();
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw1_calc_var1 = %f ms\n", compute_time);
	printf("hw1_calc_var1 value = %.15f\n", hw1_var1);


	CHECK_TIME_START;
	hw1_calc_e();
	hw1_calc_var2();
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw1_calc_var2 = %f ms\n", compute_time);
	printf("hw1_calc_var2 value = %.15f\n", hw1_var2);
	puts("");
	
	/* hw2 */
	puts("====== hw2 ======");
	printf("a, b, c : ");
	scanf("%f %f %f", &hw2_a, &hw2_b, &hw2_c);
	hw2_naive();
	hw2_safe();
	printf("naive result    : %.15f, %.15f\n", hw2_naive_ans[0], hw2_naive_ans[1]);
	printf("advanced result : %.15f, %.15f\n", hw2_pre_ans[0], hw2_pre_ans[1]);
	puts("");
	printf("Verifying naive ans    : %.15f, %.15f\n", hw2_verify(hw2_naive_ans[0]), hw2_verify(hw2_naive_ans[1]));
	printf("Verifying advanced ans : %.15f, %.15f\n", hw2_verify(hw2_pre_ans[0]), hw2_verify(hw2_pre_ans[1]));
	puts("");

	/* hw3 */

	////////////////////////////////
	////// Loop Interchange ///////
	////////////////////////////////

	int i, j;
	bool flag;

	float** arr1;
	float** arr2;
	printf("\n**********************************\n");
	printf("*        Loop Interchange        *\n");
	printf("**********************************\n");

	arr1 = (float **)malloc(sizeof(float *) * TWO_23);
	arr2 = (float **)malloc(sizeof(float *) * TWO_23);
	for (i = 0; i < TWO_23; i++)
	{
		arr1[i] = (float*)malloc(sizeof(float) * TWO_23);
		arr2[i] = (float*)malloc(sizeof(float) * TWO_23);
	}

	printf("\nThe problem is using two nested loops of %d elements with specific iteration order... \n\n", TWO_23);

	CHECK_TIME_START;
	for (j = 0; j < TWO_23; j++)
	{
		for (i = 0; i < TWO_23; i++)
		{
			arr1[i][j] = i + j + 1;
		}
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime before loop interchange is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;
	for (i = 0; i < TWO_23; i++)
	{
		for (j = 0; j < TWO_23; j++)
		{
			arr2[i][j] = i + j + 1;
		}
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime after loop interchange is %.3f(ms).\n", compute_time * 1000);


	flag = true;
	for (i = 0; i < TWO_23; i++)
	{
		for (j = 0; j < TWO_23; j++)
		{
			if (arr1[i][j] != arr2[i][j]) flag = false;
		}
	}
	if (flag) printf("Two arrays have the same elements.\n");
	else printf("There are difference between two arrays.\n");

	//////////////////////////////////////////////////////
	/////////////Loop Peeling ////////////////////////////
	//////////////////////////////////////////////////////

	printf("\n**********************************\n");
	printf("*          Loop Peeling          *\n");
	printf("**********************************\n");

	float* arr3;
	float* arr4;
	float* arr5;
	float* arr6;
	float* arr7;
	arr3 = (float*)malloc(sizeof(float) * TWO_23);
	arr4 = (float*)malloc(sizeof(float) * TWO_23);
	arr5 = (float*)malloc(sizeof(float) * TWO_23);
	arr6 = (float*)malloc(sizeof(float) * TWO_23);
	arr7 = (float*)malloc(sizeof(float) * TWO_23);

	for (i = 0; i < TWO_23; i++)
	{
		arr3[i] = i;
	}

	printf("\nThe problem is using a loop of %d elements with specific condition... \n\n", TWO_23);
	CHECK_TIME_START;

	for (i = 0; i < TWO_23; i++)
	{
		arr4[i] = (i == 0) ? arr3[i] : arr3[i] + arr4[i - 1];
	}

	CHECK_TIME_END(compute_time);
	printf("The runtime before loop peeling is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;
	arr5[0] = arr3[0];
	for (i = 1; i < TWO_23; i++)
	{
		arr5[i] = arr3[i] + arr5[i - 1];
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime after loop peeling is %.3f(ms).\n", compute_time * 1000);

	flag = true;
	for (i = 0; i < TWO_23; i++)
	{
		if (arr4[i] != arr5[i]) flag = false;
	}
	if (flag) printf("Two arrays have the same elements.\n");
	else printf("There are difference between two arrays.\n");

	//////////////////////////////////////////
	////////////////// Loop Splitting /////////////////////////

	printf("\n**********************************\n");
	printf("*        Loop Splitting          *\n");
	printf("**********************************\n");
	printf("\nThe problem is using a loop of %d elements assigned specific numbers... \n\n", TWO_23);

	CHECK_TIME_START;

	for (i = 0; i < TWO_23; i++)
	{
		arr4[i] = 2 * arr3[i] + 1;
	}

	CHECK_TIME_END(compute_time);
	printf("The runtime before loop splitting is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;

	for (i = 0; i < 100; i++)
	{
		arr5[i] = 2 * arr3[i] + 1;
	}
	for (i = 100; i < 500; i++)
	{
		arr5[i] = 2 * arr3[i] + 1;
	}
	for (i = 500; i < TWO_23; i++)
	{
		arr5[i] = 2 * arr3[i] + 1;
	}

	CHECK_TIME_END(compute_time);
	printf("The runtime after loop splitting is %.3f(ms).\n", compute_time * 1000);

	flag = true;
	for (i = 0; i < TWO_23; i++)
	{
		if (arr4[i] != arr5[i]) flag = false;
	}
	if (flag) printf("Two arrays have the same elements.\n");
	else printf("There are difference between two arrays.\n");

	/////////////////////////////////////////////////
	//////////////// Loop FIssion ///////////////////

	printf("\n**********************************\n");
	printf("*          Loop Flssion          *\n");
	printf("**********************************\n");

	printf("\nThe problem is using a loop of %d elements assigned specific numbers... \n\n", TWO_23);

	CHECK_TIME_START;

	for (i = 0; i < TWO_23; i++)
	{
		arr4[i] = 2 * arr3[i];
		arr5[i] = 3 * arr3[i] + 1;
	}

	CHECK_TIME_END(compute_time);
	printf("The runtime before loop fission is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;

	for (i = 0; i < TWO_23; i++)
	{
		arr4[i] = 2 * arr3[i];
	}
	for (i = 0; i < TWO_23; i++)
	{
		arr5[i] = 3 * arr3[i] + 1;
	}

	CHECK_TIME_END(compute_time);
	printf("The runtime after loop fission is %.3f(ms).\n", compute_time * 1000);

	//////////////////////////////////////
	//////////////Loop Unswitching ///////////////////

	printf("\n**********************************\n");
	printf("*         Loop Unswitching       *\n");
	printf("**********************************\n");

	printf("\nThe problem is using a loop of %d elements with specific condition... \n\n", TWO_23);

	float t = 3.0f;
	CHECK_TIME_START;
	for (i = 0; i < TWO_23; i++)
	{
		arr4[i] = 2 * arr3[i] + 1;
		if (t > 0) arr5[i] = t * arr3[i] + i;
	}

	CHECK_TIME_END(compute_time);
	printf("The runtime before loop unswitching is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;

	if (t > 0)
	{
		for (i = 0; i < TWO_23; i++)
		{
			arr4[i] = 2 * arr3[i] + 1;
			arr5[i] = t * arr3[i] + i;
		}
	}
	else
	{
		for (i = 0; i < TWO_23; i++)
		{
			arr4[i] = 2 * arr3[i] + 1;
		}
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime after loop unswitching is %.3f(ms).\n", compute_time * 1000);
}

void init_hw1(int cmd)
{
	float *ptr;
	int i;
	hw1_x = (float *)malloc(sizeof(float)*HW1_N);
	srand((unsigned)time(NULL));

	if (cmd)
	{
		float tmp = HW1_N;
		for (i = 0; i < HW1_N; i++)
		{
			if (i&1) tmp -= 0.0001;
			hw1_x[i] = tmp;
		}
	}
	else
	{
		ptr = hw1_x;
		for (i = 0; i < HW1_N; i++)
		{
			*ptr++ = ((float)rand() / RAND_MAX) * 2;
		}
	}
}
void hw1_calc_e()
{
	hw1_E = 0.0;

	for (int i = 0; i < HW1_N; i++)
	{
		hw1_E += hw1_x[i];
	}
	hw1_E *= (1 / (float)HW1_N);
}

void hw1_calc_var1()
{
	hw1_var1 = 0.0;
	int i;
	float tmp1 = 0.0;
	float tmp2 = 0.0;

	for (i = 0; i < HW1_N; i++)
	{
		tmp1 += pow(hw1_x[i], 2);
	}
	tmp1 = (float)tmp1 * (float)HW1_N;

	for (i = 0; i < HW1_N; i++)
	{
		tmp2 += hw1_x[i];
	}
	tmp2 = pow(tmp2, 2);

	hw1_var1 = (float)(tmp1 - tmp2) / (float)(HW1_N * (HW1_N - 1));
}

void hw1_calc_var2()
{
	int i;
	hw1_var2 = 0.0;
	for (i = 0; i < HW1_N; i++)
	{
		hw1_var2 += pow((hw1_x[i] - hw1_E), 2);
	}
	hw1_var2 /= (float)(HW1_N - 1);
}

void hw2_naive()
{
	double tmp;
	tmp = (float)(hw2_b * hw2_b) - (float)(4.0 * hw2_a * hw2_c);
	tmp = sqrt(tmp);
	//printf("tmp = %.15f\n", tmp);
	hw2_naive_ans[0] = (float)(-1.0) * hw2_b + tmp;
	hw2_naive_ans[1] = (float)(-1.0) * hw2_b - tmp;

	hw2_naive_ans[0] /= (float)2.0 * hw2_a;
	hw2_naive_ans[1] /= (float)2.0 * hw2_a;
}

void hw2_safe()
{
	double tmp;
	tmp = (float)(hw2_b * hw2_b) - (float)(4.0 * hw2_a * hw2_c);
	tmp = sqrt(tmp);
	if (hw2_b > 0)
	{
		hw2_pre_ans[0] = (float)(-2.0) * hw2_c / (float)(hw2_b + tmp);
	}
	else
	{
		hw2_pre_ans[0] = (float)((-1.0) * hw2_b + tmp) / (float)(2.0 * hw2_a);
	}
	if (hw2_b < 0)
	{
		hw2_pre_ans[1] = (float)(-2.0) * hw2_c / (float)(hw2_b - tmp);
	}
	else
	{
		hw2_pre_ans[1] = (float)((-1.0) * hw2_b - tmp) / (float)(2.0 * hw2_a);
	}
}

float hw2_verify(float x)
{
	return hw2_a * x * x + hw2_b*x + hw2_c;
}
