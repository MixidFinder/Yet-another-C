#include <stdio.h>

#define MAXLEN 10

int input(int *arr, int *len, int *c);
void output(int *arr, int len);
void cycle(int *arr, int len, int c);

int main() {
    int len, arr[MAXLEN], c;
    if (input(arr, &len, &c)) {
        cycle(arr, len, c);
        output(arr, len);
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *arr, int *len, int *c) {
    int flag = 1;
    if (scanf("%d", len) != 1 || *len < 1 || *len > MAXLEN) {
        flag = 0;
    }
    for (int *p = arr; p - arr < *len && flag == 1; p++) {
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
    if (flag == 1) {
        if (scanf("%d", c) != 1 && flag != 1) {
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

void cycle(int *arr, int len, int c) {
    c = c % len;
    if (c < 0) {
        c += len;
    }
    int eff_shift = (len - c) % len;
    int temp[len];
    for (int i = 0; i < len; i++) {
        temp[(i + eff_shift) % len] = arr[i];
    }
    for (int i = 0; i < len; i++) {
        arr[i] = temp[i];
    }
}