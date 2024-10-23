#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

int s21_strlen(char *s) {
    int count = 0;

    if (s != NULL) {
        for (; *(s + count); count++)
            ;
    }

    return count;
}

int s21_strcmp(char *s, char *ss) {
    int res = 0;
    if (s != NULL && ss != NULL) {
        for (; *s && *ss && *s == *ss; s++, ss++) {
        }
        res = *s - *ss;
    }

    return res;
}

char *s21_strcpy(char *source) {
    char *cop = NULL;
    if (source != NULL) {
        int len = s21_strlen(source) + 1;
        cop = (char *)malloc(len * sizeof(char));

        for (int i = 0; i < len; i++) {
            cop[i] = source[i];
        }
    }

    return cop;
}