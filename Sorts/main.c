#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/*long long int abs(long long int x) {
    if (x < 0)
        return -x;
    return x;
}*/

void *inordered(int n, long long int *a) {
    srand(time(NULL));
    long long int lim = LLONG_MAX / n * 2;
    long long int step = (((long long)rand() << 32) | rand()) % lim;
    a[0] = LLONG_MIN + step;
    for (int i = 1; i < n; i++) {
        step = (((long long)rand() << 32) | rand()) % lim;
        a[i] = a[i - 1] + step;
    }
}

void *postordered(int n, long long int *a) {
    srand(time(NULL));
    long long int lim = LLONG_MAX / n * 2;
    long long int step = (((long long)rand() << 32) | rand()) % lim;
    a[n - 1] = LLONG_MIN + step;
    for (int i = n - 2; i >= 0; i--) {
        step = (((long long)rand() << 32) | rand()) % lim;
        a[i] = a[i - 1] + step;
    }
}

void *randomed(int n, long long int *a) {
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        a[i] = ((long long int)rand() << 32) | rand();
}

/*
void qsort(int n, long long int *a) {

}

void psort(int n, long long int *a) {

}*/

void arrprint(int n, long long int *a) {
    for (int i = 0; i < n; i++) {
        printf("%25lld ", a[i]);
        if ((i + 1) % 3 == 0) printf("\n");
    }
}

int main(void) {
    int n = 10;

    long long int *arr1 = malloc(n * sizeof(long long int));
    inordered(n, arr1);
    arrprint(n, arr1);

    printf("\n================================================================================\n");

    long long int *arr2 = malloc(n * sizeof(long long int));
    postordered(n, arr2);
    arrprint(n, arr2);

    printf("\n================================================================================\n");

    long long int *arr3 = malloc(n * sizeof(long long int));
    randomed(n, arr3);
    arrprint(n, arr3);

    printf("\n================================================================================\n");

    long long int *arr4 = malloc(n * sizeof(long long int));
    randomed(n, arr4);
    arrprint(n, arr4);

    return 0;
}
