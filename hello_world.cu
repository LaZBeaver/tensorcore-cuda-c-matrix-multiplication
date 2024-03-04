#include <stdio.h>
#include <cuda.h>

__global__ void testGPU(){
    printf("Hello this is GPU\n");
}

int main(){
    printf("Hi from CPU\n");
    
    testGPU<<<1, 1>>>();
    cudaDeviceSynchronize();

    return 0;
}