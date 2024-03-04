#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <mma.h>

#define WARP_SIZE 32

// Matrix A = (M_tiles * K_tiles)
// Matrix B = (K_tiles * N_tiles)
// Matrix C & D = (M_tiles * N_tiles)
// Each tile is equal to 16 element

#define M 16
#define N 16
#define K 16

#define M_TILES 256
#define N_TILES 256
#define K_TILES 256

#define M_TOTAL (M * M_TILES)
#define N_TOTAL (N * N_TILES)
#define K_TOTAL (K * K_TILES)

using namespace nvcuda;

void InitMatrix(half *A, half *B, float *C)
{
	for (int i = 0; i < M_TOTAL * K_TOTAL; i++)
		A[i] = __float2half((float)rand() / RAND_MAX);

	for (int i = 0; i < K_TOTAL * N_TOTAL; i++)
		B[i] = __float2half((float)rand() / RAND_MAX);

	for (int i = 0; i < M_TOTAL * N_TOTAL; i++)
		C[i] = 0.0f;
}



__global__ void WMMAF16TensorCore(half *A, half *B, float *C, float *D)
{
	int ix = (blockIdx.x * blockDim.x + threadIdx.x)/WARP_SIZE;
	int iy = (blockIdx.y * blockDim.y + threadIdx.y);
	
	wmma::fragment<wmma::matrix_a, M, N, K, half, wmma::row_major> a_frag;
	wmma::fragment<wmma::matrix_b, M, N, K, half, wmma::col_major> b_frag;
	wmma::fragment<wmma::accumulator, M, N, K, float> ab_frag;
	wmma::fragment<wmma::accumulator, M, N, K, float> c_frag;
	
	wmma::fill_fragment(ab_frag, 0.0f);

	// AB = A*B
	int a_col, a_row, b_col, b_row, c_col, c_row;
	a_row = ix * M;
	b_row = iy * N;
	for (int k=0; k<K_TOTAL; k+=K) {
		a_col = b_col = k;

		if (a_row < M_TOTAL && a_col < K_TOTAL && b_row < K_TOTAL && b_col < N_TOTAL) {
			// Load the inputs
			wmma::load_matrix_sync(a_frag, A + a_col + a_row * M_TOTAL, M_TOTAL);
			wmma::load_matrix_sync(b_frag, B + b_col + b_col * K_TOTAL, K_TOTAL);

			// Perform the matrix multiplication
			wmma::mma_sync(ab_frag, a_frag, b_frag, ab_frag);
		}
	}

	// D = AB + C
	c_col = b_row;
	c_row = a_row;
	if (c_row < M_TOTAL && c_col < N_TOTAL) {
		wmma::load_matrix_sync(c_frag, C + c_col + c_row * N_TOTAL, N_TOTAL, wmma::mem_row_major);

		for (int i = 0; i < c_frag.num_elements; i++) {
			c_frag.x[i] = ab_frag.x[i] + c_frag.x[i];
		}

		// Store the output
		wmma::store_matrix_sync(D + c_col + c_row * N_TOTAL, c_frag, N_TOTAL, wmma::mem_row_major);
	}
}


int main()
{

	half *A;
	half *B;
	float *C;
	float *D;

	cudaMallocManaged((void **)&A, sizeof(half) * M_TOTAL * K_TOTAL);
	cudaMallocManaged((void **)&B, sizeof(half) * K_TOTAL * N_TOTAL);
	cudaMallocManaged((void **)&C, sizeof(float) * M_TOTAL * N_TOTAL);
	cudaMallocManaged((void **)&D, sizeof(float) * M_TOTAL * N_TOTAL);
	
	InitMatrix(A, B, C);

	printf("A: %d x %d\n", M_TOTAL, K_TOTAL);
	printf("B: %d x %d\n", K_TOTAL, N_TOTAL);
	printf("C: %d x %d\n", M_TOTAL, N_TOTAL);
	
	dim3 gridDim, blockDim;
	blockDim.x = 4 * WARP_SIZE; 
	blockDim.y = 4;

	gridDim.x = (M_TOTAL + (M * blockDim.x / WARP_SIZE - 1)) / (M * blockDim.x / WARP_SIZE);
	gridDim.y = (N_TOTAL + N * blockDim.y - 1) / (N * blockDim.y);

	WMMAF16TensorCore<<<gridDim, blockDim>>>(A, B, C, D);
	
	cudaDeviceSynchronize();

	cudaFree(A);
	cudaFree(B);
	cudaFree(C);
	cudaFree(D);

	return 0;
}