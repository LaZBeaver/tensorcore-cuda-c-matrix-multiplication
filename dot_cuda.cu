#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void dot(float *a, float *b, float *c, int a_r, int b_c, int a_b_s){
    
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < a_r && col < b_c){
        float tmp_sum = 0;
        for (int i = 0; i < a_b_s; i++){
            // a_c == b_r == a_b_s
            tmp_sum += a[row * a_b_s + i] * b[i * b_c + col];
        }
        c[row * b_c + col] = tmp_sum;
    }

}

void init(float *m, int r, int c){
    for (int i = 0; i < r * c; i++)
        m[i] = (float)rand() / RAND_MAX;
        // m[i] = rand() % 10;
        
}

void print(float *m, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++)
            printf("%f ", m[i * c + j]);
        printf("\n");
    }
}

int main(){
    int a_r = 1024;
    int a_b_s = 1024;
    int b_c = 1024;
    
    size_t a_bytes = a_r * a_b_s * sizeof(float);
    size_t b_bytes = a_b_s * b_c * sizeof(float);
    size_t c_bytes = a_r * b_c * sizeof(float);

    float *a, *b, *c;

    cudaMallocManaged(&a, a_bytes);
    cudaMallocManaged(&b, b_bytes);
    cudaMallocManaged(&c, c_bytes);

    init(a, a_r, a_b_s);
    init(b, a_b_s, b_c);
    
    int threads_per_dim_in_block = 16;
    
    int blocks_x = (b_c - 1) / threads_per_dim_in_block + 1;
    int blocks_y = (a_r - 1) / threads_per_dim_in_block + 1;
    dim3 BLOCKS(blocks_x, blocks_y, 1);
    
    dim3 THREADS(threads_per_dim_in_block, threads_per_dim_in_block, 1);
    

    dot<<<BLOCKS, THREADS>>>(a, b, c, a_r, b_c, a_b_s);

    cudaDeviceSynchronize();

    // print(a, a_r, a_b_s);
    // print(b, a_b_s, b_c);
    // print(c, a_r, b_c);

    return 0;
}