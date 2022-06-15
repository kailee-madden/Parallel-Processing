#include <math.h>
#include <string.h>
#include <stdio.h>
#include "timer.h"


// define mesh size, number of blocks NBL and threads per block TPB
#define NN 4096
#define NM 4096
#define NBLX 32
#define NBLY 32
#define TPBX 16
#define TPBY 16


// -------------------------------------------------------
// CUDA device function that performs jacobi method
// -------------------------------------------------------
__global__ void jacobi(long int *Anew, long int *A, int maxrow, int maxcol){

    size_t rowinit = threadIdx.x + blockDim.x * blockIdx.x;
    size_t colinit = threadIdx.y + blockDim.y * blockIdx.y;
    size_t rowstride = gridDim.x * blockDim.x;
    size_t colstride = gridDim.y * blockDim.y;

    int iter = 0;
    int iter_max = 1000;
    long int tol = 1.0e-6;
    long int error = 1.0;

    // until our error is what we want or we have done too many iterations, keep recalculating A matrix and error
    while ( error > tol && iter < iter_max ){
        error = 0.0;
        // for loop to calculate the new A matrix and the error
        // here we use our variables based on threadIdx, blockDim, blockIdx, and gridDim
        for (size_t j = rowinit; j < NN; j += rowstride) {
            for (size_t i = colinit; i < NM; i += colstride) {
                Anew[j*NM +i] = 0.25 * ( A[j*NM + i+1] + A[j*NM + i-1] + A[(j-1)*NM +i] + A[(j+1)*NM +i]);
                error = max( error, abs(Anew[j*NM +i] - A[j*NM +i]));
            }
        }
        // Synchronize threads - make sure all threads are done before continuing
        __syncthreads();    

        // for loop to set A matrix equal to the new A matrix
        // here we use our variables based on threadIdx, blockDim, blockIdx, and gridDim
        for (size_t j = rowinit; j < NM; j += rowstride) {
            for (size_t i = colinit; i < NM; i += colstride) {
                A[j*NM +i] = Anew[j*NM +i];    
            }
        }

        // Synchronize threads - make sure all threads are done before continuing
        __syncthreads();
    }

}


// ------------
// main program
// ------------
int main(void){
    // variables
    int n = NN;
    int m = NM;
    long int *A;
    long int *Anew;
    size_t size = n * m * sizeof(long int);

    // allocate host memory
    A = (long int *) malloc(size);

    // initialize matrix
    for (int j = 0; j < n; j++){
        for(int i=0; i<m; i++){
            A[j*m +i] = 1.0;
        }
    }
    printf("Jacobi relaxation Calculation: %d x %d mesh\n", n, m);
    // allocate device memory
    cudaMalloc((void **)&Anew, size);

    // copy input data to device
    cudaMemcpy(Anew, A, size, cudaMemcpyHostToDevice);

    StartTimer();

    // Apply jacobi by launching a sufficient number of blocks
    printf("\n---------------------------\n");
    printf("Launching jacobi kernel\n");
    printf("---------------------------\n");
    printf("Matrix elements   = %d x %d = %d\n",NN,NM,NN*NM);
    printf("Blocks            = %d x %d = %d\n",NBLX,NBLY,NBLX*NBLY);
    printf("Threads per block = %d x %d = %d\n",TPBX,TPBY,TPBX*TPBY);
    printf("Kernel copies     = %d\n",NBLX*NBLY*TPBX*TPBY);

    jacobi<<<dim3(NBLX,NBLY),dim3(TPBX,TPBY)>>>(Anew, A, n, m);

    // copy results back to host
    cudaMemcpy(Anew, A, size, cudaMemcpyDeviceToHost);
  
    // deallocate memory
    cudaFree(Anew);

    double runtime = GetTimer();
    printf(" total: %f s\n", runtime / 1000);
    return 0;
}
