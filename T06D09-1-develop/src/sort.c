#include <stdio.h>

#define MAXLEN 10

int input(int *arr);
void output(int *arr);
void sort(int *arr);

int main() {
    int arr[MAXLEN];
    if (input(arr)) {
        sort(arr);
        output(arr);
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *arr) {
    int flag = 1;
    for (int *p = arr; p - arr < MAXLEN; p++) {
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

void output(int *arr) {
    for (int *p = arr; p - arr < MAXLEN; p++) {
        if ((p - arr) > 0) {
            printf(" ");
        }
        printf("%d", *p);
    }
}

void sort(int *arr) {
    for (int i = 1; i < MAXLEN; i++) {
        int key = *(arr + i);
        int j = i - 1;
        while (j >= 0 && *(arr + j) > key) {
            *(arr + j + 1) = *(arr + j);
            j--;
        }
        *(arr + j + 1) = key;
    }
}