#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        squaring(data, n);
        output(data, n);

        return 0;
    }

    printf("n/a");

    return 1;
}

int input(int *a, int *n) {
    scanf("%d", n);

    if (*n < 1 || *n > NMAX) {
        return 0;
    }
    for (int *p = a; p - a < *n; p++) {
        scanf("%d", p);
    }

    return 1;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

void squaring(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        *p = (*p) * (*p);
    }
}