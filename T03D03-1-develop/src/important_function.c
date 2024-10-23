#include <math.h>
#include <stdio.h>

float calc(float a);

int main() {
    float a;
    char ch;

    int res = scanf("%lf%c", &a, &ch);

    if (res == 2 && ch == '\n' && (a >= 0.01 || a <= -0.01)) {
        printf("%.1lf\n", calc(a));
        return 0;
    } else {
        printf("n/a\n");
        return 1;
    }
    printf("n/a");

    return 1;
}

float calc(float a) {
    return 7e-3 * pow(a, 4) + ((22.8 * cbrt(a) - 1e3) * a + 3) / (a * a / 2) - a * pow(10 + a, 2 / a) - 1.01;
}
