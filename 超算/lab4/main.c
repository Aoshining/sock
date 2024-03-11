#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "judge.h"

struct timeval global_tv;
double global_time_start, global_time_end;

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if (argc != 2) {
        printf("./pcg should have a input file as parameter, e.x. ./pcg input_1.bin.\n");
        exit(1);
    }

    /* get size */
    int size;
    FILE *in = fopen(argv[1], "rb");
    fread(&size, sizeof(int), 1, in);
    printf("input size = %d\n", size);
    double A[size][size], b[size];

    /* input data */
    if (rank == 0) {
    	input(argv[1], size, A, b);
    	gettimeofday(&global_tv, NULL);
    	global_time_start = (double)(global_tv.tv_sec) + (double)(global_tv.tv_usec) * 1e-6;
	}
    
    for (int i = 0; i < 10; ++i) {
        PCG(size, A, b);
    }
    if (rank == 0) {
    	gettimeofday(&global_tv, NULL);
    	global_time_end = (double)(global_tv.tv_sec) + (double)(global_tv.tv_usec) * 1e-6;
	}

    /* output result */
    printf("total run time = %.4lfs.\n", global_time_end - global_time_start);
    
    MPI_Finalize();
}
