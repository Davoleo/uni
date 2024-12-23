#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

static void HandleError(cudaError_t err,
                        const char *file,
                        int line)
{
    if (err != cudaSuccess)
    {
        printf("%s in %s at line %d\n", cudaGetErrorString(err),
               file, line);
        exit(EXIT_FAILURE);
    }
}

#define HANDLE_ERROR(err) (HandleError(err, __FILE__, __LINE__))

const int threadsPerBlock = 256;

__global__ void add(float *res)
{
    __shared__ float shr[threadsPerBlock];

    //// qui ogni thread scrive il proprio indice
    //// da modificare con il calcolo del proprio relativo pezzo di rettangoli
    //// utilizzare blockIdx.x, blockDim.x e gridDim.x per calcolare la propria posizione e le divisioni da gestire
    int x = threadIdx.x + blockDim.x * blockIdx.x;

    //cpi calculation: f1
    shr[threadIdx.x] = (1.0 / (1.0 + x*x));

    //cpi calculation: f2
    //shr[threadIdx.x] = (sqrt(1-x*x));
    

    __syncthreads();

    // for reductions, threadsPerBlock must be a power of 2 // because of the following code
    int i = blockDim.x / 2;
    while (i != 0)
    {
        if (threadIdx.x < i)
            shr[threadIdx.x] += shr[threadIdx.x + i];
        __syncthreads();
        i /= 2;
    }
    if (threadIdx.x == 0)
        res[blockIdx.x] = shr[threadIdx.x];
}

int main(void)
{

    //Time 
    float time_passed;
    cudaEvent_t start;
    cudaEvent_t stop;

    int nblocks = 128;
    printf("hi\n");

    float *res = (float *)malloc(nblocks * sizeof(float));
    float *dev_res;
    HANDLE_ERROR(cudaMalloc((void **)&dev_res, nblocks * sizeof(float)));
    
    printf("start\n");
    cudaEventCreate(&start);
    cudaEventRecord(start, NULL);

    add<<<nblocks, threadsPerBlock>>>(dev_res);

    puts("end");
    cudaEventCreate(&stop);
    cudaEventRecord(stop, NULL);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&time_passed, start, stop);
    
    HANDLE_ERROR(cudaMemcpy(res, dev_res, nblocks * sizeof(float), cudaMemcpyDeviceToHost));
    printf("ok %f, time passed: %f\n", res[0], time_passed);

    float total = 0;
    for (int i = 0; i < nblocks; i++)
    {
        printf("Block %d: %f\n", i, res[i]);
        total += res[i];
    }

    printf("Somma %f\n", total);
    //    cudaFree( dev_res );

    return 0;
}
