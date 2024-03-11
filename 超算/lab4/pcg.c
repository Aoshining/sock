#include "judge.h"

double dot(double a[], double b[], int size){
    double dot_sum = 0;
    for (int i = 0; i < size; ++i) {
        dot_sum += a[i] * b[i];
    }
    return dot_sum;
}


void MatrixMulVec(int size, double A[][size], double x[], double b[]) {
    int i, j;
	#pragma omp parallel for
	for (int i = 0; i < size; ++i) {
        b[i] = 0;
        for (int j = 0; j < size; ++j) {
            b[i] += A[i][j] * x[j];
        }
    }
}


void PCG(int size, double A[][size], double b[]) {

    int rank, comm_size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
	
	if (rank == 0)start_timer();
	
	int sendcounts[comm_size];
	int displs[comm_size];
	for (int i = 0; i < comm_size; ++i){
		sendcounts[i] = size / comm_size + (i < comm_size - 1 ? 0 : size % comm_size);
		displs[i] = (i ? sendcounts[i - 1] + displs[i - 1] : 0);
	}
	int cur_size = sendcounts[rank]; 
    double cur_A[cur_size][size], cur_b[cur_size], cur_r[cur_size], cur_x[cur_size], cur_z[cur_size], cur_p[cur_size];
    double x[size], p[size],A_dot_p[size];
	double alpha, beta, r_dot_z, cur_A_dot_p[cur_size];

	MPI_Bcast(A, size * size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(b, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatterv(b, sendcounts, displs, MPI_DOUBLE,cur_b, cur_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    for(int i = 0; i < cur_size; ++i)
		for(int j = 0; j < size; ++j)
			cur_A[i][j] = A[i + displs[rank]][j];	
	for (int i = 0; i < cur_size; ++i){
        cur_x[i] = 0;
        cur_r[i] = cur_b[i];
        cur_z[i] = cur_r[i] / cur_A[i][i + displs[rank]];
        cur_p[i] = cur_z[i];
    }

    int iter = 0;
    double loss = 0;
    
    r_dot_z = dot(cur_r, cur_z, cur_size);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allreduce(MPI_IN_PLACE, &r_dot_z, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    do {
		MPI_Gatherv(cur_p, cur_size, MPI_DOUBLE, p, sendcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);            
        MatrixMulVec(size, A, p, A_dot_p);
		MPI_Scatterv(A_dot_p, sendcounts, displs, MPI_DOUBLE,cur_A_dot_p, cur_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		
		double p_dot_Adotp=dot(cur_p, cur_A_dot_p, cur_size);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allreduce(MPI_IN_PLACE, &p_dot_Adotp, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		alpha = r_dot_z / p_dot_Adotp;

        for (int i = 0; i < cur_size; ++i) {
            cur_x[i] += alpha * cur_p[i];
        }

        int quit = 1;
        loss = 0;
        for (int i = 0; i < cur_size; ++i) {
            cur_r[i] = cur_r[i] - alpha * cur_A_dot_p[i];
            if (cur_r[i]) quit = 0;
            loss += fabs(cur_r[i]);
        }
        MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allreduce(MPI_IN_PLACE, &quit, 1, MPI_INT, MPI_LAND, MPI_COMM_WORLD);
		MPI_Allreduce(MPI_IN_PLACE, &loss, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        if (quit) break;

        for (int i = 0; i < cur_size; ++i) {
            cur_z[i] = cur_r[i] / cur_A[i][i + displs[rank]];
        }

        double temp = dot(cur_z, cur_r, cur_size);
        MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allreduce(MPI_IN_PLACE, &temp, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		beta = temp / r_dot_z;
        r_dot_z = temp;

        for (int i = 0; i < cur_size; ++i) {
            cur_p[i] = cur_z[i] + beta * cur_p[i];
        }
        
    }
    while (++iter < MAXITER && loss > EPI);

	MPI_Gatherv(cur_x, cur_size, MPI_DOUBLE, x, sendcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) check(size, A, x, b, iter);
}
