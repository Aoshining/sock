#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>
#include"mpi.h"
#include"omp.h"


// Calculate sum of distance while combining different pivots. Complexity : O( n^2 )
double SumDistance(const int k, const int n, const int dim, double* coord, int* pivots){
    int rank,process,i;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&process);
    int size1=n/process;
	int size2=n%process;
    int sc[process],displs[process];
    displs[0]=0;
    for(i=0;i<process;i++)
    {
        if(i<size2){
           sc[i]=dim*(size1+1); 
        }
        else{
            sc[i]=dim*size1;
        }
        if(i!=0)
        {
            displs[i]=displs[i-1]+sc[i-1];
        }
    }
    int new_n=sc[rank]/dim;
    double new_coord[dim*new_n];

    
    MPI_Scatterv(coord,sc,displs,MPI_DOUBLE,new_coord,new_n*dim,MPI_DOUBLE,0,MPI_COMM_WORLD);

    double rebuiltCoord[new_n * k];
    double n_rebuiltCoord[n * k];
    for(i=0; i<n*k; i++){
        n_rebuiltCoord[i] = 0;
    }
    for(i=0; i<new_n*k; i++){
        rebuiltCoord[i] = 0;
    }

    // Rebuild coordinates. New coordinate of one point is its distance to each pivot.
    for(i=0; i<new_n; i++){
        int ki;
        for(ki=0; ki<k; ki++){
            double distance = 0;
            int pivoti = pivots[ki];
            int j;
            for(j=0; j<dim; j++){
                distance += pow(coord[pivoti*dim + j] - new_coord[i*dim + j] ,2);
            }
            rebuiltCoord[i*k + ki] = sqrt(distance);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    int SC[process],Displs[process];
    Displs[0]=0;
    for(i=0;i<process;i++)
    {
        SC[i]=sc[i]/dim*k;
        if(i!=0)
        Displs[i]=Displs[i-1]+SC[i-1];
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gatherv(rebuiltCoord,new_n*k,MPI_DOUBLE,n_rebuiltCoord,SC,Displs,MPI_DOUBLE,0,MPI_COMM_WORLD);
    // Calculate the sum of Chebyshev distance with rebuilt coordinates between every points

    double chebyshevSum = 0;
    #pragma omp parallel for schedule(static) reduction(+:chebyshevSum) 
    for(i=0; i<n; i++){
        int j;
        #pragma simd
        for(j=i; j<n; j++){
            double chebyshev = 0;
            int ki;
            for(ki=0; ki<k; ki++){
                double dis = fabs(n_rebuiltCoord[i*k + ki] - n_rebuiltCoord[j*k + ki]);
                chebyshev = dis>chebyshev ? dis : chebyshev;
            }
            chebyshevSum += chebyshev;
        }
    }
    return chebyshevSum*2;
}

// Recursive function Combination() : combine pivots and calculate the sum of distance while combining different pivots.
// ki  : current depth of the recursion
// k   : number of pivots
// n   : number of points
// dim : dimension of metric space
// M   : number of combinations to store
// coord  : coordinates of points
// pivots : indexes of pivots  
// maxDistanceSum  : the largest M distance sum
// maxDisSumPivots : the top M pivots combinations
// minDistanceSum  : the smallest M distance sum
// minDisSumPivots : the bottom M pivots combinations
void Combination(const int k, const int n, const int dim, const int M, double* coord, int* pivots,
                 double* maxDistanceSum, int* maxDisSumPivots, double* minDistanceSum, int* minDisSumPivots){
    int ki = 0; // Initialize depth to 0
    int i = 0; // Initialize index to 0
    int a;
    #pragma omp parallel private(i,a)
    while (ki >= 0) {
        if (ki == k) { // If we have selected k pivots
            // Calculate sum of distance while combining different pivots.
            double distanceSum = SumDistance(k, n, dim, coord, pivots);

            // Store the results in maxDistanceSum, maxDisSumPivots, minDistanceSum, and minDisSumPivots
            maxDistanceSum[M] = distanceSum;
            minDistanceSum[M] = distanceSum;
            for (a = 0; a < k; a++) {
                maxDisSumPivots[M * k + a] = pivots[a];
                minDisSumPivots[M * k + a] = pivots[a];
            }

            // Sort maxDistanceSum and minDistanceSum arrays
            for (a = M; a > 0; a--) {
                if (maxDistanceSum[a] > maxDistanceSum[a - 1]) {
                    double temp = maxDistanceSum[a];
                    maxDistanceSum[a] = maxDistanceSum[a - 1];
                    maxDistanceSum[a - 1] = temp;
                    for (int kj = 0; kj < k; kj++) {
                        int temp = maxDisSumPivots[a * k + kj];
                        maxDisSumPivots[a * k + kj] = maxDisSumPivots[(a - 1) * k + kj];
                        maxDisSumPivots[(a - 1) * k + kj] = temp;
                    }
                }
                if (minDistanceSum[a] < minDistanceSum[a - 1]) {
                    double temp = minDistanceSum[a];
                    minDistanceSum[a] = minDistanceSum[a - 1];
                    minDistanceSum[a - 1] = temp;
                    for (int kj = 0; kj < k; kj++) {
                        int temp = minDisSumPivots[a * k + kj];
                        minDisSumPivots[a * k + kj] = minDisSumPivots[(a - 1) * k + kj];
                        minDisSumPivots[(a - 1) * k + kj] = temp;
                    }
                }
            }
            ki--; // Decrement depth to backtrack
        } else {
            // Increment the index to consider the next point
            i++;
            if (i < n) {
                // Set the next pivot
                pivots[ki] = i;
                ki++; // Increment depth to go deeper
            } else {
                // We have reached the end for this depth, so we backtrack
                ki--;
                if (ki >= 0) {
                    // Increment the index of the previous depth to consider the next point
                    i = pivots[ki];
                }
            }
        }
    }
}


int main(int argc, char* argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    // filename : input file namespace
    char* filename = (char*)"uniformvector-2dim-5h.txt";
    if( argc==2 ) {
        filename = argv[1];
    }  else if(argc != 1) {
        printf("Usage: ./pivot <filename>\n");
        return -1;
    }
    // M : number of combinations to store
    const int M = 1000;
    // dim : dimension of metric space
    int dim;
    // n : number of points
    int n;
    // k : number of pivots
    int k;

    // Read parameter
    FILE* file = fopen(filename, "r");
    if( file == NULL ) {
        printf("%s file not found.\n", filename);
        return -1;
    }
    fscanf(file, "%d", &dim);
    fscanf(file, "%d", &n);
    fscanf(file, "%d", &k);
    if(rank==0)
    printf("dim = %d, n = %d, k = %d\n", dim, n, k);

   
    struct timeval start;
    // Read Data
    double* coord = (double*)malloc(sizeof(double) * dim * n);
    int i;
    for(i=0; i<n; i++){
        int j;
        for(j=0; j<dim; j++){
            fscanf(file, "%lf", &coord[i*dim + j]);
        }
    }
    fclose(file);
      // Start timing
    if(rank == 0)
    {
        
        gettimeofday(&start, NULL);
        
    }
       

    // maxDistanceSum : the largest M distance sum
    double* maxDistanceSum = (double*)malloc(sizeof(double) * (M+1));
    for(i=0; i<M; i++){
        maxDistanceSum[i] = 0;
    }
    // maxDisSumPivots : the top M pivots combinations
    int* maxDisSumPivots = (int*)malloc(sizeof(int) * k * (M+1));
    for(i=0; i<M; i++){
        int ki;
        for(ki=0; ki<k; ki++){
            maxDisSumPivots[i*k + ki] = 0;
        }
    }
    // minDistanceSum : the smallest M distance sum
    double* minDistanceSum = (double*)malloc(sizeof(double) * (M+1));
    for(i=0; i<M; i++){
        minDistanceSum[i] = __DBL_MAX__;
    }
    // minDisSumPivots : the bottom M pivots combinations
    int* minDisSumPivots = (int*)malloc(sizeof(int) * k * (M+1));
    for(i=0; i<M; i++){
        int ki;
        for(ki=0; ki<k; ki++){
            minDisSumPivots[i*k + ki] = 0;
        }
    }

    // temp : indexes of pivots with dummy array head
    int* temp = (int*)malloc(sizeof(int) * (k+1));
    temp[0] = -1;

    // Main loop. Combine different pivots with recursive function and evaluate them. Complexity : O( n^(k+2) )
    Combination(k, n, dim, M, coord, &temp[1], maxDistanceSum, maxDisSumPivots, minDistanceSum, minDisSumPivots);
    struct timeval end;
    // End timing
    if(rank == 0)
    {
        
        gettimeofday (&end, NULL);
        printf("Using time : %f ms\n", (end.tv_sec-start.tv_sec)*1000.0+(end.tv_usec-start.tv_usec)/1000.0);

        // Store the result
        char result_name[100];
        sprintf(result_name,"result1D%03dN%03dK%03d",dim,n,k);
        FILE* out = fopen(result_name, "w");
        for(i=0; i<M; i++){
            int ki;
            for(ki=0; ki<k-1; ki++){
                fprintf(out, "%d ", maxDisSumPivots[i*k + ki]);
            }
            fprintf(out, "%d\n", maxDisSumPivots[i*k + k-1]);
        }
        for(i=0; i<M; i++){
            int ki;
            for(ki=0; ki<k-1; ki++){
                fprintf(out, "%d ", minDisSumPivots[i*k + ki]);
            }
            fprintf(out, "%d\n", minDisSumPivots[i*k + k-1]);
        }
        fclose(out);

        // Log
        int ki;
        printf("max : ");
        for(ki=0; ki<k; ki++){
            printf("%d ", maxDisSumPivots[ki]);
        }
        printf("%lf\n", maxDistanceSum[0]);
        printf("min : ");
        for(ki=0; ki<k; ki++){
            printf("%d ", minDisSumPivots[ki]);
        }
        printf("%lf\n", minDistanceSum[0]);
    }

    // for(i=0; i<M; i++){
        // int ki;
        // for(ki=0; ki<k; ki++){
            // printf("%d\t", maxDisSumPivots[i*k + ki]);
        // }
        // printf("%lf\n", maxDistanceSum[i]);
    // }
    // for(i=0; i<M; i++){
        // int ki;
        // for(ki=0; ki<k; ki++){
            // printf("%d\t", minDisSumPivots[i*k + ki]);
        // }
        // printf("%lf\n", minDistanceSum[i]);
    // }
    MPI_Finalize();
    return 0;
    
}