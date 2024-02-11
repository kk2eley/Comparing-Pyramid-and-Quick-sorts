#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


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

int swp = 0;
int cmp = 0;

void swap(long long int* a, long long int* b) {
    swp++;
    long long int temp = *a;
    *a = *b;
    *b = temp;
}

long long int compare(long long int a, long long int b) {
    cmp++;
    return ((a < 0) ? -a : a) - ((b < 0) ? -b : b);
}


int partition(int n, long long int *a) {
    long long int pivot = a[n/2];
    int i = 0, j = n - 1;
    do{
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j) {
            swap(&a[i], &a[j]);
            i++;
            j--;
        }
    } while (i <= j);
    return i;
}

void qsortCustom(int n, long long int *a) {
    if (n > 2) {
        int rif = partition(n, a);
        qsortCustom(rif , a);
        qsortCustom(n - rif, a + rif);
    } else if (n == 2 && a[0] > a[1]) {
        swap(&a[0], &a[1]);
    }
}

/*
void psort(int n, long long int *a) {

}*/

void arrprint(int n, long long int *a) {
    for (int i = 0; i < n; i++) {
        printf("%5lld ", a[i]);
        if ((i + 1) % n == 0) printf("\n");
    }
}

int main(void) {
    int n = 2;
/*
    long long int *arr1 = malloc(n * sizeof(long long int));
    inordered(n, arr1);

    long long int *arr2 = malloc(n * sizeof(long long int));
    postordered(n, arr2);

    long long int *arr3 = malloc(n * sizeof(long long int));
    randomed(n, arr3);
*/

    long long int *arr4 = malloc(n * sizeof(long long int));
    randomed(n, arr4);
    for (int i = 0; i < n; i++)
        arr4[i] %= 100;
    arrprint(n, arr4);
    qsortCustom(n, arr4);
    arrprint(n, arr4);

    return 0;
}
