#include <stdio.h>

int find_max(int a, int b);

int main() {
    int a, b;
    char ch;

    int res = scanf("%d %d%c", &a, &b, &ch);
    if (res == 3 && ch == '\n') {
        printf("%d", find_max(a, b));
        return 0;
    } else {
        printf("n/a");
        return 1;
    }
}

int find_max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
