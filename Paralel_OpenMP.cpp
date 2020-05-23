

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#define N    100            /* number of rows in matrix A */
                 /* number of columns in matrix B */

int main(int argc, char* argv[])
{
    int	tid, nthreads, i, j, k, chunk;
    double	a[N][N],           /* matrix A to be multiplied */
        b[N][N],           /* matrix B to be multiplied */
        c[N][N];           /* result matrix C */

    chunk = 10;                    /* set loop iteration chunk size */
    srand(time(0));
double sTime = omp_get_wtime();
    /*** Spawn a parallel region explicitly scoping all variables ***/
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Starting matrix multiple example with %d threads\n", nthreads);
            printf("Initializing matrices...\n");
        }
        /*** Initialize matrices ***/
#pragma omp for schedule (static, chunk) 
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                a[i][j] = 1 + rand() % 50;
#pragma omp for schedule (static, chunk)
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                b[i][j] = 1 + rand() % 20;
#pragma omp for schedule (static, chunk)
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                c[i][j] = 0;
       
        /*** Do matrix multiply sharing iterations on outer loop ***/
        /*** Display who does which iterations for demonstration purposes ***/
        printf("Thread %d starting matrix multiply...\n", tid);
#pragma omp for schedule (static, chunk)
        
        
        for (i = 0; i < N; i++)
        {
            printf("Thread=%d did row=%d\n", tid, i);
            for (j = 0; j < N; j++)
                for (k = 0; k < N; k++)
                    c[i][j] += a[i][k] * b[k][j];
        }
    }   /*** End of parallel region ***/

    printf("******************************************************\n");
    printf("Result Matrix:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%6.0f   ", c[i][j]);
        printf("\n");
    }
    printf("******************************************************\n");
    printf("Done.\n");
    double eTime = omp_get_wtime();
    double T = eTime - sTime;
    printf("\nTime Required: %3.9f ", (T));

   // cout << "\nTime Required: " << (eTime - sTime) << endl;
}