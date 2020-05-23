/*
#include <iostream>
#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <mpi.h>  
#include <stdlib.h>
#include "conio.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstdlib> 

*/

#define N 10
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include "mpi.h"


void print_results(int a[N][N]);
void print_result(double S);
int main(int argc, char* argv[])
{

    int i, j, k, rank, size, tag = 99, blksz, sum = 0;
    int a[N][N];
   int b[N][N];
   int c[N][N];
    int aa[N], cc[N];
    srand(time(0));


    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            a[i][j] = 1 + rand() % 50;
            b[i][j] = 1 + rand() % 20;
        }

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   double start_time = MPI_Wtime();
    //scatter rows of first matrix to different processes     
    MPI_Scatter(a, N * N / size, MPI_INT, aa, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    //broadcast second matrix to all processes
    MPI_Bcast(b, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    //perform vector multiplication by all processes
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            sum = sum + aa[j] * b[j][i];             
        }
        cc[i] = sum;
        sum = 0;
    }

    MPI_Gather(cc, N * N / size, MPI_INT, c, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();
    MPI_Finalize();
    if (rank == 0)                        
        print_results(c);

   
    double T = (end_time - start_time) ;
    if (rank == 0)
    print_result(T);
    
}


void print_result(double S)
{
   printf("\nTime Required: %6.9f ", (S));
         
   
}
void print_results(int a[N][N])
{
    int i, j;

  // printf("\n\n%s\n", prompt);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf(" %d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");


}