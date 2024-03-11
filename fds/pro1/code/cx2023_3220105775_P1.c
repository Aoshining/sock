#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 100 //Matrix Side Length
#define K1 1 //Iteration of Algorithm 1
#define K2 100 //Iteration of Algorithm 2
#define K3 1000 //Iteration of Algorithm 3

clock_t start, stop;
double duration;

int sum_N6(int a[][N])//Algorithm 1 O(N^6)
{
    int sum, maxsum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        //Iterate over each element of the matrix as the upper-left element of the submatrix
            for (int p = i; p < N; p++)
                for (int q = j; q < N; q++)
                //Use the upper-left element as the starting point, and then traverse all the elements to its lower-right as the lower-right element of the sub-matrix
                {
                    sum = 0;
                    for (int m = i; m <= p; m++)
                        for (int n = j; n <= q; n++)
                            sum += a[m][n];
                    if (sum > maxsum) maxsum = sum;
                    //After determining the upper-left and lower-right corners, iterate over all the elements in between to obtain the sum of each sub-matrix element
                }
    return maxsum;
}

int sum_N4(int a[][N])//Algorithm 2 O(N^4)
{
    int sum, maxsum = 0, dp[N][N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if(i==0&&j==0) dp[i][j] = a[i][j];
            else if(i==0) dp[i][j] = dp[i][j-1] + a[i][j];
            else if(j==0) dp[i][j] = dp[i-1][j] + a[i][j];
            else dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + a[i][j];
        }
        //Initialize the two-dimensional prefix sum, dp[i][j] stores the sum of all elements in the matrix enclosed by row 1, column 1 to row i, column j
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            sum = 0;
            for (int p = i; p < N; p++)
                for (int q = j; q < N; q++)
                {
                    if(i==0&&j==0) sum = dp[p][q];
                    else if(i==0) sum = dp[p][q] - dp[p][j-1];
                    else if(j==0) sum = dp[p][q] - dp[i-1][q];
                    else sum = dp[p][q] - dp[p][j-1] - dp[i-1][q] + dp[i-1][j-1];
                    if (sum > maxsum) maxsum = sum;
                }
                //The sum of all elements in the matrix with [i][j] as the upper-left corner and [p][q] as the lower-right corner can be derived directly from the two-dimensional prefix sum, eliminating the need for two-fold iterations to traverse through all of the elements in the sum
        }
    return maxsum;
}

int sum_N3(int a[][N])//Algorithm 3 O(N^3) (Bonus)
{
    int maxsum = 0, dp[N][N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if(i==0) dp[i][j] = a[i][j];
            else dp[i][j] = dp[i-1][j] + a[i][j];
        }
        //Initialize the two-dimensional prefix sum, dp[i][j] stores the jth column element sums from row 0 to row i
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
        //Traverse the subsequence of rows by first determining the upper and lower bounds in terms of rows
        {
            int rowsum[N] = {0}, sum = 0;
            for(int k = 0; k < N; k++)
            {
                if(i==0) rowsum[k] = dp[j][k];
                else rowsum[k] = dp[j][k] - dp[i-1][k];
                //Then all the elements of the submatrix with different rows but the same columns are summed into a single number, thus obtaining a one-dimensional matrix that compresses the submatrix
                sum += rowsum[k];
                if (sum > maxsum) maxsum = sum;
                else if (sum < 0) sum = 0;
                //Finally, the on-line algorithm is used for the one-dimensional matrix to find its maximal sub-matrix
            }
        }
    return maxsum;
}

int main()
{
    int a[N][N], maxsum;
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = (rand() % 10 + 1) * ((rand() % 2) ? 1 : -1);
    //Randomly generate an N*N array of non-zero integers ranging from -10 to 10 elements

    start = clock();
    for (int i = 0; i < K1; i++)//Algorithm 1 iteration K1
        maxsum = sum_N6(a);
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK;
    printf("Algorithm1:MAXIMUM SUBMATRIX SUM = %d, Iterations = %d, Ticks = %ld, Total Time = %e, Duration = %e\n", maxsum, K1, stop-start, duration, duration / K1);//Output Algorithm 1 Result

    start = clock();
    for (int i = 0; i < K2; i++)//Algorithm 2 iteration K2
        maxsum = sum_N4(a);
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK;
    printf("Algorithm2:MAXIMUM SUBMATRIX SUM = %d, Iterations = %d, Ticks = %ld, Total Time = %e, Duration = %e\n", maxsum, K2, stop-start, duration, duration / K2);//Output Algorithm 2 Result

    start = clock();
    for (int i = 0; i < K3; i++)//Algorithm 3 iteration K3
        maxsum = sum_N3(a);
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK;
    printf("Algorithm3:MAXIMUM SUBMATRIX SUM = %d, Iterations = %d, Ticks = %ld, Total Time = %e, Duration = %e", maxsum, K3, stop-start, duration, duration / K3);//Output Algorithm 3 Result

    return 0;
}