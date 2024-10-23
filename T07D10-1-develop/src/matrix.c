#include <stdio.h>
#include <stdlib.h>

#define MAXX 100
#define MAXY 100

int input(int *x, int *y);
int **create_matrix_2(int x, int y);
int **create_matrix_3(int x, int y);
int **create_matrix_4(int x, int y);
int fill_matr(int **matr, int x, int y);
int fill_matr_stat(int matr[MAXX][MAXY], int x, int y);
void output_stat(int matr[MAXX][MAXY], int x, int y);
void output(int **matr, int x, int y);

int main() {
    int choise, x, y, flag = 1;
    int **matr = NULL;
    int matr_stat[MAXX][MAXY];
    if (scanf("%d", &choise) != 1 || choise < 1 || choise > 4) {
        flag = 0;
    }

    if (choise == 1 && flag != 0) {
        if (input(&x, &y)) {
            if (fill_matr_stat(matr_stat, x, y)) {
                output_stat(matr_stat, x, y);
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    } else if (choise == 2 && flag != 0) {
        if (input(&x, &y)) {
            matr = create_matrix_2(x, y);
            if (fill_matr(matr, x, y)) {
                output(matr, x, y);
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    } else if (choise == 3 && flag != 0) {
        if (input(&x, &y)) {
            matr = create_matrix_3(x, y);
            if (fill_matr(matr, x, y)) {
                output(matr, x, y);
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    } else if (choise == 4 && flag != 0) {
        if (input(&x, &y)) {
            matr = create_matrix_4(x, y);
            if (fill_matr(matr, x, y)) {
                output(matr, x, y);
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    }

    if (flag != 1) {
        printf("n/a");
    }
    if (matr != NULL) {
        for (int i = 0; i < x; i++) {
            free(matr[i]);
        }
        free(matr);
    }

    return 0;
}

int input(int *x, int *y) {
    int flag = 1;
    if (scanf("%d %d", x, y) != 2 || (*x < 2 && *y < 2) || (*x > MAXX && *y > MAXY)) {
        flag = 0;
    }

    return flag;
}

int **create_matrix_2(int x, int y) {
    int **matr = (int **)calloc(x, sizeof(int *));

    for (int i = 0; i < x; i++) {
        matr[i] = (int *)calloc(y, sizeof(int));
    }

    return matr;
}

int **create_matrix_3(int x, int y) {
    int **matr = calloc(x, sizeof(int *));
    for (int i = 0; i < x; i++) {
        matr[i] = calloc(x * y, sizeof(int)) + y * i;
    }

    return matr;
}

int **create_matrix_4(int x, int y) {
    int **matr = malloc(x * y * sizeof(int) + x * sizeof(int *));
    int count = 0;
    for (int i = 0; i < x; i++) {
        matr[i] = (int *)(matr + x) + y * i;
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            matr[i][j] = ++count;
        }
    }

    return matr;
}

int fill_matr(int **matr, int x, int y) {
    int flag = 1;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (scanf("%d", &matr[i][j]) == 1) {
                continue;
            } else {
                flag = 0;
            }
        }
    }

    return flag;
}

int fill_matr_stat(int matr[MAXX][MAXY], int x, int y) {
    int flag = 1;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (scanf("%d", &matr[i][j]) != 1) {
                flag = 0;
            }
        }
    }
    return flag;
}

void output(int **matr, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%d", matr[i][j]);
            if (j < y - 1) {
                printf(" ");
            }
        }
        if (i < x - 1) {
            printf("\n");
        }
    }
}

void output_stat(int matr[MAXX][MAXY], int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%d", matr[i][j]);
            if (j < y - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}