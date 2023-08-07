#include <stdio.h>
#include <omp.h>

#define M 4
#define N 5

int main() {
    int a[M][N] =
        {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20}};
    int b[M][N] =
        {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20}};
    int c[M][N] = {0};
    int i, j;

    #pragma omp parallel for collapse(2) shared (a,b,c) private(j)
    // private is to ensure each thread has a private variable j, i is already private since it is outer loop
    // collapse allows you to parallelize multiple loops in a nest without introducing nested parallelism
    // n = number of loops
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

    // for (i = 0; i < M; i++) {
    //     #pragma omp parallel for
    //     // i runs in parallel but j runs in a thread each (j threads)
    //     for (j = 0; j < N; j++) {
    //         c[i][j] = a[i][j] * b[i][j];
    //     }
    // }

    printf("Values of C:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
