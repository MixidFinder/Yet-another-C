#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 10

int input(int **arr, int *len);
void output(int *arr, int len);
void sort(int *arr, int len);

int main() {
    int len, *arr;
    if (input(&arr, &len)) {
        sort(arr, len);
        output(arr, len);

    } else {
        printf("n/a");
    }
    free(arr);
    return 0;
}

int input(int **arr, int *len) {
    int flag = 1;
    if (scanf("%d", len) != 1 || *len < 1) {
        flag = 0;
    }
    *arr = (int *)calloc(*len, sizeof(int));
    if (arr == NULL) {
        flag = 0;
    }
    for (int *p = *arr; p - *arr < *len && flag == 1; p++) {
        double chck = 0;
        if (scanf("%lf", &chck) == 1) {
            *p = chck;
            if (*p == chck) {
                continue;
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    }
    return flag;
}

void output(int *arr, int len) {
    for (int *p = arr; p - arr < len; p++) {
        if ((p - arr) > 0) {
            printf(" ");
        }
        printf("%d", *p);
    }
}

void sort(int *arr, int len) {
    for (int i = 1; i < len; i++) {
        int key = *(arr + i);
        int j = i - 1;
        while (j >= 0 && *(arr + j) > key) {
            *(arr + j + 1) = *(arr + j);
            j--;
        }
        *(arr + j + 1) = key;
    }
}