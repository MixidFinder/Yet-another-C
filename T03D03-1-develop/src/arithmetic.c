#include <stdio.h>

int sum(int a, int b);
int diff(int a, int b);
int prod(int a, int b);
int quot(int a, int b);

int main() {
    int a, b;
    char ch;

    int res = scanf("%d %d%c", &a, &b, &ch);

    if (res == 3 && ch == '\n') {
        printf("%d ", sum(a, b));
        printf("%d ", diff(a, b));
        printf("%d ", prod(a, b));
    } else {
        printf("n/a");
        return 1;
    }

    if (b == 0) {
        printf("n/a");
        return 1;
    } else {
        printf("%d", quot(a, b));
    }

    return 0;
}

int sum(int a, int b) { return a + b; }

int diff(int a, int b) { return a - b; }

int prod(int a, int b) { return a * b; }

int quot(int a, int b) { return a / b; }
