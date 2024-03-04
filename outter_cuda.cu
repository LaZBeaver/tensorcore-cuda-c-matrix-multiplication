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

__global__ void sum(float *a, float *b, float *c, int n){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < n)
        c[tid] = a[tid] + b[tid];
}

void init(float *m, int r, int c){
    for (int i = 0; i < r * c; i++)
        // m[i] = rand() % 10;
        m[i] = (float)rand() / RAND_MAX;
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

    float *h_a;
    float *h_b;

    float *d_a;
    float *d_b;
    float *d_c;

    size_t a_bytes = a_r * 1 * sizeof(float);
    size_t b_bytes = 1 * b_c * sizeof(float);
    size_t c_bytes = a_r * b_c * sizeof(float);

    // A place to store all the partials to add them later all together
    float *partials[a_b_s];

    for (int i = 0; i < a_b_s; i++){
        
        h_a = (float*)malloc(a_bytes);
        h_b = (float*)malloc(b_bytes);
        partials[i] = (float*)malloc(c_bytes);

        init (h_a, a_r, 1);
        init (h_b, 1, b_c);

        cudaMalloc(&d_a, a_bytes);
        cudaMalloc(&d_b, b_bytes);
        cudaMalloc(&d_c, c_bytes);

        cudaMemcpy(d_a, h_a, a_bytes, cudaMemcpyHostToDevice);
        cudaMemcpy(d_b, h_b, b_bytes, cudaMemcpyHostToDevice);

        int threads_per_dim_in_block = 16;

        int blocks_x = (b_c - 1) / threads_per_dim_in_block + 1;
        int blocks_y = (a_r - 1) / threads_per_dim_in_block + 1;

        dim3 BLOCKS(blocks_x, blocks_y);
        dim3 THREADS(threads_per_dim_in_block, threads_per_dim_in_block);

        dot<<<BLOCKS, THREADS>>>(d_a, d_b, d_c, a_r, b_c, 1);

        cudaMemcpy(partials[i], d_c, c_bytes, cudaMemcpyDeviceToHost);

        // printf("For %d col of a and row of b we have:\n", i);
        // print(h_a, a_r, 1);
        // print(h_b, 1, b_c);
        // print(partials[i], a_r, b_c);
        // printf("\n");

        free(h_a);
        free(h_b);

        cudaFree(d_a);
        cudaFree(d_b);
        cudaFree(d_c);

    }

    cudaDeviceSynchronize();

    // Now we have all the partials in the partials[] and we only need to sum the co-responding elements
    // for this we use the kernel that sums up to vectores and since the placment in menmory is actually
    // row majored we make a final result which is the same size as it needs to be then initialize it to
    // zero and then pass that with each elemt of partials[] to get the sum.

    float *result;
    result = (float*)malloc(c_bytes);
    for (int i = 0; i < a_r * b_c; i++)
        result[i] = 0;
    
    for (int i = 0; i < a_b_s; i++){

        cudaMalloc(&d_a, c_bytes);
        cudaMalloc(&d_b, c_bytes);
        cudaMalloc(&d_c, c_bytes);

        cudaMemcpy(d_a, partials[i], c_bytes, cudaMemcpyHostToDevice);
        cudaMemcpy(d_b, result, c_bytes, cudaMemcpyHostToDevice);

        int THREADS = 256;
        int BLOCKS = (a_r * b_c - 1) / THREADS + 1;

        sum<<<BLOCKS, THREADS>>>(d_a, d_b, d_c, a_r * b_c);

        cudaMemcpy(result, d_c, c_bytes, cudaMemcpyDeviceToHost);

        free(partials[i]);

        cudaFree(d_a);
        cudaFree(d_b);
        cudaFree(d_c);        
    
    }

    cudaDeviceSynchronize();
    
    // print(result, a_r, b_c);
    
    return 0;
}