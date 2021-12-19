
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <assert.h>

//1 prac 2
//2 prac 3
#define prac 1


#define CUDA_CALL(x) { const cudaError_t a = (x); if(a != cudaSuccess) { printf("\nCuda Error: %s (err_num=%d) at line:%d\n", cudaGetErrorString(a), a, __LINE__); cudaDeviceReset(); assert(0);}}
typedef float TIMER_T;
#define USE_CPU_TIMER 1
#define USE_GPU_TIMER 1

#if USE_CPU_TIMER == 1
__int64 start, freq, end;
#define CHECK_TIME_START { QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start); }
#define CHECK_TIME_END(a) { QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f)); }
#else
#define CHECK_TIME_START
#define CHECK_TIME_END(a)
#endif

#if USE_GPU_TIMER == 1
cudaEvent_t cuda_timer_start, cuda_timer_stop;
#define CUDA_STREAM_0 (0)

// CUDA event 객체를 사용하여 커널 실행시간 측정
void create_device_timer()
{
	CUDA_CALL(cudaEventCreate(&cuda_timer_start));
	CUDA_CALL(cudaEventCreate(&cuda_timer_stop));
}

void destroy_device_timer()
{
	CUDA_CALL(cudaEventDestroy(cuda_timer_start));
	CUDA_CALL(cudaEventDestroy(cuda_timer_stop));
}

inline void start_device_timer()
{
	cudaEventRecord(cuda_timer_start, CUDA_STREAM_0);
}

inline TIMER_T stop_device_timer()
{
	TIMER_T ms;
	cudaEventRecord(cuda_timer_stop, CUDA_STREAM_0);
	cudaEventSynchronize(cuda_timer_stop);

	cudaEventElapsedTime(&ms, cuda_timer_start, cuda_timer_stop);
	return ms;
}

#define CHECK_TIME_INIT_GPU() { create_device_timer(); }
#define CHECK_TIME_START_GPU() { start_device_timer(); }
#define CHECK_TIME_END_GPU(a) { a = stop_device_timer(); }
#define CHECK_TIME_DEST_GPU() { destroy_device_timer(); }
#else
#define CHECK_TIME_INIT_GPU()
#define CHECK_TIME_START_GPU()
#define CHECK_TIME_END_GPU(a)
#define CHECK_TIME_DEST_GPU()
#endif

#define BLOCK_SIZE 32
#define MAX_N_ELEMENTS (1 << 20)

TIMER_T compute_time = 0;
TIMER_T device_time = 0;

int N_EQU;
float* X0_GPU, * X1_GPU;
float* FX0_GPU, * FX1_GPU;
float* X0, * X1;
float* FX0, * FX1;
float* A, * B, * C;


cudaError_t find_roots_GPU(float* A, float* B, float* C, float* X0_GPU, float* X1_GPU, float* FX0_GPU, float* FX1_GPU);

__global__ void find_roots_Kernel(float* d_A, float* d_B, float* d_C, float* d_X0, float* d_X1, float* d_FX0, float* d_FX1)
{

    int id;
    float a, b, c, d, x0, x1, temp;

    id = blockDim.x * blockIdx.x + threadIdx.x;
    a = d_A[id];
    b = d_B[id];
    c = d_C[id];
    d = sqrtf(b * b - 4.0f * a * c);
    temp = 1.0f / (2.0f * a);
    d_X0[id] = x0 = (-b - d) * temp;
    d_X1[id] = x1 = (-b + d) * temp;
    d_FX0[id] = (a * x0 + b) * x0 + c;
    d_FX1[id] = (a * x1 + b) * x1 + c;

}

void find_roots_CPU(float* A, float* B, float* C, float* X0, float* X1, float* FX0, float* FX1, int n) {
    int j;
    float a, b, c, d, x0, x1, temp;

    for (j = 0; j < n; ++j)
    {
        a = A[j];
        b = B[j];
        c = C[j];
        d = sqrtf(b * b - 4.0f * a * c);
        temp = 1.0f / (2.0f * a);
        X0[j] = x0 = (-b - d) * temp;
        X1[j] = x1 = (-b + d) * temp;
        FX0[j] = (a * x0 + b) * x0 + c;
        FX1[j] = (a * x1 + b) * x1 + c;
    }
}

void init_bin_file(int size) {
    FILE* fp = fopen("A.bin", "wb");
    int random_num;
    
    srand((unsigned)time(NULL));
    printf(">>> Binary File init Started<<<\n");
    fwrite(&size, sizeof(int), 1, fp);
    
    for (int i = 0; i < size; ++i)
    {
        random_num = (float)((float)rand() / RAND_MAX * 20.0f - 10.0f);
        fwrite(&random_num, sizeof(float), 1, fp);
    }
    fclose(fp);

    fp = fopen("B.bin", "wb");
    fwrite(&size, sizeof(int), 1, fp);

    for (int i = 0; i < size; ++i)
    {
        random_num = (float)((float)rand() / RAND_MAX * 1000.0f + 100.0f);
        fwrite(&random_num, sizeof(float), 1, fp);
    }
    fclose(fp);

    fp = fopen("C.bin", "wb");
    fwrite(&size, sizeof(int), 1, fp);

    for (int i = 0; i < size; ++i)
    {
        random_num = (float)((float)rand() / RAND_MAX * 20.0f - 10.0f);
        fwrite(&random_num, sizeof(float), 1, fp);
    }

    fclose(fp);
    printf(">>> Binary File init End <<\n\n");
}

void read_bin_file()
{
    FILE* fp = fopen("A.bin", "rb");
    /*Todo*/

    printf(">>> Binary File Read Started <<<\n");
    fread(&N_EQU, sizeof(int), 1, fp);

    A = new float[N_EQU];
    B = new float[N_EQU];
    C = new float[N_EQU];
    X0 = new float[N_EQU];
    X1 = new float[N_EQU];
    FX0 = new float[N_EQU];
    FX1 = new float[N_EQU];
    X0_GPU = new float[N_EQU];
    X1_GPU = new float[N_EQU];
    FX0_GPU = new float[N_EQU];
    FX1_GPU = new float[N_EQU];


    fread(A, sizeof(float), N_EQU, fp);

    fclose(fp);

    fp = fopen("B.bin", "rb");
    fread(&N_EQU, sizeof(int), 1, fp);
    fread(B, sizeof(float), 1, fp);
    fclose(fp);

    fp = fopen("C.bin", "rb");
    fread(&N_EQU, sizeof(int), 1, fp);
    fread(C, sizeof(float), 1, fp);
    fclose(fp);

    printf(">>> Binary File Read End <<<\n\n");
}

int main()
{
    int i;
    FILE* fp;
    init_bin_file(MAX_N_ELEMENTS);
    read_bin_file();

    printf("N_EQUATION : %d.\n", N_EQU);

    //CPU 
    printf(">>> find_roots_CPU Started <<<\n");
    CHECK_TIME_START;
    find_roots_CPU(A, B, C, X0, X1, FX0, FX1, N_EQU);
    CHECK_TIME_END(compute_time);
    printf(">>> find_roots_CPU End <<<\n\n");
    printf("CPU time = %.6f\n", compute_time);

    //GPU
    printf(">>> find_roots_GPU Started <<<\n");
    find_roots_GPU(A, B, C, X0_GPU, X1_GPU, FX0_GPU, FX1_GPU);
    printf(">>> find_roots_GPU End <<<\n\n");
    printf("GPU time = %.6f\n", device_time);


    fp = fopen("X0.bin", "wb");
    if (!fp)
    {
        fprintf(stderr, "Error: cannot open the output file...\n");
        exit(-1);
    }

    fwrite(&N_EQU, sizeof(int), 1, fp);
    for (i = 0; i < N_EQU; ++i)
        fwrite(&X0_GPU[i], sizeof(float), 1, fp);
    fclose(fp);


    fp = fopen("X1.bin", "wb");
    if (!fp)
    {
        fprintf(stderr, "Error: cannot open the output file...\n");
        exit(-1);
    }

    fwrite(&N_EQU, sizeof(int), 1, fp);

    for (i = 0; i < N_EQU; ++i)
        fwrite(&X1_GPU[i], sizeof(float), 1, fp);
    fclose(fp);


    fp = fopen("FX0.bin", "wb");
    if (!fp)
    {
        fprintf(stderr, "Error: cannot open the output file...\n");
        exit(-1);
    }
    fwrite(&N_EQU, sizeof(int), 1, fp);

    for (i = 0; i < N_EQU; ++i)
        fwrite(&FX0_GPU[i], sizeof(float), 1, fp);
    fclose(fp);
    printf(">>> end <<<\n\n");


    fp = fopen("FX1.bin", "wb");
    if (!fp)
    {
        fprintf(stderr, "Error: cannot open the output file...\n");
        exit(-1);
    }

    fwrite(&N_EQU, sizeof(int), 1, fp);
    for (i = 0; i < N_EQU; ++i)
        fwrite(&X0_GPU[i], sizeof(float), 1, fp);

    fclose(fp);

    return (0);
}


cudaError_t find_roots_GPU(float* A, float* B, float* C, float* X0_GPU, float* X1_GPU, float* FX0_GPU, float* FX1_GPU)
{
    CHECK_TIME_INIT_GPU();

    cudaError_t cudaStatus;
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }
    /*Todo*/

    float* d_A, * d_B, * d_C;
    float* d_X, * d_Y;
    float* d_FX, * d_FY;

    size_t size;

    size = N_EQU * sizeof(float);

    CUDA_CALL(cudaMalloc(&d_A, size))

        CUDA_CALL(cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice))

        CUDA_CALL(cudaMalloc(&d_B, size))

        CUDA_CALL(cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice))

        CUDA_CALL(cudaMalloc(&d_C, size))

        CUDA_CALL(cudaMemcpy(d_C, C, size, cudaMemcpyHostToDevice))


        CUDA_CALL(cudaMalloc(&d_X, size))
        CUDA_CALL(cudaMalloc(&d_Y, size))
        CUDA_CALL(cudaMalloc(&d_FX, size))
        CUDA_CALL(cudaMalloc(&d_FY, size))

        size = N_EQU;

    CHECK_TIME_START_GPU()

        dim3 dimBlock(BLOCK_SIZE, 1);
    dim3 dimGrid(N_EQU / dimBlock.x, 1);

    find_roots_Kernel << < dimGrid, dimBlock >> > (d_A, d_B, d_C, d_X, d_Y, d_FX, d_FY);

    CHECK_TIME_END_GPU(device_time)
        size = N_EQU * sizeof(float);

    CUDA_CALL(cudaGetLastError())

        CUDA_CALL(cudaDeviceSynchronize())
        CUDA_CALL(cudaMemcpy(X0_GPU, d_X, size, cudaMemcpyDeviceToHost))

        CUDA_CALL(cudaMemcpy(X1_GPU, d_Y, size, cudaMemcpyDeviceToHost))

        CUDA_CALL(cudaMemcpy(FX0_GPU, d_FX, size, cudaMemcpyDeviceToHost))

        CUDA_CALL(cudaMemcpy(FX1_GPU, d_FY, size, cudaMemcpyDeviceToHost))


        CHECK_TIME_DEST_GPU();

Error:
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    cudaFree(d_X);
    cudaFree(d_Y);
    cudaFree(d_FX);
    cudaFree(d_FY);

    return cudaStatus;
}