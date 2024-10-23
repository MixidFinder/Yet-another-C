#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "data_process.h"

int main(void) {
    double *data = NULL;
    int n = 0;

    if (input(&data, &n)) {
        if (normalization(data, n)) {
            output(data, n);
        } else {
            printf("ERROR");
        }
    } else {
        printf("n/a");
    }

    free(data);

    return 0;
}
