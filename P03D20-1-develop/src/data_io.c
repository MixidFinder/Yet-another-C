#include "data_io.h"

#include <stdio.h>
#include <stdlib.h>

char *Input(void) {
    char *inp = (char *)malloc(sizeof(char) * 256);
    int len = 0, size = 1;
    char ch = getchar();

    while (ch != '\0' && ch != '\n') {
        inp[len++] = ch;

        if (len >= size) {
            size *= 2;
            char *new_inp = (char *)realloc(inp, size * sizeof(char));
            inp = new_inp;
        }
        ch = getchar();
    }

    return inp;
}

void Output(char **matr) {
    for (int i = 0; i < LEN_Y; ++i) {
        for (int j = 0; j < LEN_X; ++j) {
            printf("%c", matr[i][j]);
        }
        printf("\n");
    }
}
void DebugPrint(int error_flag) {
    printf("Ошибка входных данных, попробуйте снова  error_flag = %d\n", error_flag);
}

char **CreateDynamic2dArray(int *is_valid_input) {
    int rows = LEN_Y;
    int cols = LEN_X;
    char **data = (char **)malloc(rows * sizeof(char *) + rows * cols * sizeof(char));
    if (data == NULL) {
        *is_valid_input = 0;
        return NULL;
    }

    char *data_rows = (char *)(data + rows);
    for (int i = 0; i < rows; i++) {
        data[i] = data_rows + i * cols;
    }

    *is_valid_input = 1;
    return data;
}

void Clear2dArr(char **array) {
    for (int i = 0; i < LEN_Y; i++) {
        for (int j = 0; j < LEN_X; j++) {
            array[i][j] = '.';
        }
    }
}

void ClearMyScreen() {
    for (int i = 0; i < LEN_Y * 2; i++) {
        printf("\n");
    }
}