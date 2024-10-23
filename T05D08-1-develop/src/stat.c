#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

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
    printf("\n");
}

int max(int *a, int n) {
    int max_v = *a;
    for (int *p = a; p - a < n; p++) {
        if (max_v < *p) {
            max_v = *p;
        }
    }

    return max_v;
}

int min(int *a, int n) {
    int min_v = *a;
    for (int *p = a; p - a < n; p++) {
        if (min_v > *p) {
            min_v = *p;
        }
    }

    return min_v;
}

double mean(int *a, int n) {
    double mean_v = 0.0;

    for (int *p = a; p - a < n; p++) {
        mean_v += *p;
    }

    return mean_v / n;
}

double variance(int *a, int n) {
    double variance_v = 0.0;
    double mean_v = mean(a, n);

    for (int *p = a; p - a < n; p++) {
        variance_v += (*p - mean_v) * (*p - mean_v);
    }

    return variance_v / mean_v;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}