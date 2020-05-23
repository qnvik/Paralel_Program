#define N  100
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctime>


void print_results(double a[N][N]);

int main()
{
    
    int i, j, k, rank, size, tag = 99, blksz, sum = 0;
   double  a[N][N] ;
   double b[N][N];
   double c[N][N];
   srand(time(0));
   double start_time = clock();
   for (i = 0; i < N; i++)
       for (j = 0; j < N; j++)
       {
           a[i][j] = 1 + rand() % 50;
           b[i][j] = 1 + rand() % 20;

       }


    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k <N; k++)
                c[i][j] += (a[i][k] * b[k][j]);

        }

             
        print_results(c);

        double end_time = clock();
        double T = (end_time - start_time)/1000;
        printf("\nTime Required: %6.9f ", (T));
}

void print_results(double a[N][N])
{
    int i, j;

    // printf("\n\n%s\n", prompt);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%6.0f", a[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

  
}