#include <stdio.h>

void check(double a, double b);

int main() {
    double a, b;
    char ch;
    int res = scanf("%lf %lf%c", &a, &b, &ch);

    if (res == 3 && ch == '\n') {
        check(a, b);
        return 0;
    } else {
        printf("n/a");
        return 1;
    }
}

void check(double a, double b) {
    if ((a * a + b * b) < 25.0 && (a * a + b * b) > -25.0) {
        printf("GOTCHA");
    } else {
        printf("MISS");
    }
}
