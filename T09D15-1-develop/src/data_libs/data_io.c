#include "data_io.h"

#include <stdio.h>
#include <stdlib.h>

int input(double **data, int *n) {
    int flag = 1;

    if (scanf("%d", n) == 1 && *n > 0) {
        *data = (double *)calloc(*n, sizeof(double));
        if (*data != NULL) {
            for (int i = 0; i < *n && scanf("%lf", &(*data)[i]) == 1; i++) {
            }
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }

    return flag;
}

void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        printf(i == 0 ? "%lf" : " %lf", data[i]);
    }
}