#include <stdio.h>
#include <omp.h>
#define N 20

int main() {
    int a[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int b[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int c[N] = {0};
    int i;

    #pragma omp parallel for shared(a, b, c) private(i)
    for (i = 0; i < N; i++) {
        if (i > 0) {
            // #pragma omp critical
            // this is incorrect, this algorithm cannot be parallelised
            c[i] = c[i - 1] + (a[i] * b[i]);
        } else {
            c[i] = (a[i] * b[i]);
        }
    }

    printf("Values of C:\n");
    for (i = 0; i < N; i++) {
        printf("%d\t", c[i]);
    }
    printf("\n");
    return 0;
}
