/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/
#include <stdio.h>

#define NMAX 30

int input(int *a, int *n);
double dispersion(int *a, int n, double mean_v);
int find_valid_number(int *a, int n, double mean_v, double dispersion_v);
double mean(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        double mean_v = mean(data, n);
        double dispersion_v = dispersion(data, n, mean_v);

        int result = find_valid_number(data, n, mean_v, dispersion_v);
        printf("%d", result);

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

double dispersion(int *a, int n, double mean_v) {
    double dispersion_v = 0;
    for (int *p = a; p - a < n; p++) {
        double diff = *p - mean_v;
        dispersion_v += diff * diff;
    }

    return dispersion_v / n;
}

int find_valid_number(int *a, int n, double mean_v, double dispersion_v) {
    for (int *p = a; p - a < n; p++) {
        if (*p != 0 && *p % 2 == 0 && *p >= mean_v && *p <= mean_v + 3 * dispersion_v) {
            return *p;
        }
    }
    return 0;
}

double mean(int *a, int n) {
    double mean_v = 0.0;

    for (int *p = a; p - a < n; p++) {
        mean_v += *p;
    }

    return mean_v / n;
}
