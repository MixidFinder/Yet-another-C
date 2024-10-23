#include <stdio.h>

#define MAXLEN 10

int input(int *arr, int *len);
void output(int *arr, int len);
int sum_numbers(int *arr, int len);
int find_numbers(int *arr, int len, int number, int *numbers);

int main() {
    int len, arr[MAXLEN], numbers[MAXLEN] = {0};
    if (input(arr, &len)) {
        int sum_numbers_v = sum_numbers(arr, len);
        if (sum_numbers_v != 0 && find_numbers(arr, len, sum_numbers_v, numbers)) {
            printf("%d\n", sum_numbers_v);
            output(numbers, len);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *arr, int *len) {
    int flag = 1;
    if (scanf("%d", len) != 1 || *len < 1 || *len > MAXLEN) {
        flag = 0;
    }
    for (int *p = arr; p - arr < *len && flag != 0; p++) {
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
    for (int *p = arr; p - arr < len && *p != 0; p++) {
        if ((p - arr) > 0) {
            printf(" ");
        }
        printf("%d", *p);
    }
}

int sum_numbers(int *arr, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] % 2 == 0) {
            sum = sum + arr[i];
        }
    }
    return sum;
}

int find_numbers(int *arr, int len, int number, int *numbers) {
    int iter = 0;
    for (int i = 0; i <= len; i++) {
        if (arr[i] != 0 && number % arr[i] == 0) {
            numbers[iter++] = arr[i];
        }
    }
    return iter > 0;
}