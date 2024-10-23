#include "data_parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO (.)(.) -(2+5)
// TODO -1 = (0 - 1)  если предыдущий оператор или начало строки или скобка открывающая

char *ParseCharArr(char *array, int *error_flag) {
    if (!*error_flag) CheckEmptyArr(array, error_flag);  // 1 flag not NULL
    if (!*error_flag) CheckArrLenth(array, error_flag);  // 2 flag not empty
    MakeMyArrayBigger(&array);
    if (!*error_flag) CheckEmptyArr(array, error_flag);  // 1 flag not NULL

    /*     char *temp_array = MakeSameSizeArray(&array);
        if (!*error_flag) CheckEmptyArr(temp_array, error_flag);  // 1 flag not NULL

        if (!*error_flag) MakeArrLower(array);                      // lowercase for all
        if (!*error_flag) CheckBrackets(array, error_flag);         // 3 || 4 flag
        if (!*error_flag) CheckDowbleOperators(array, error_flag);  // 5 flag
        if (!*error_flag) CheckStartOperators(array, error_flag);   // 6 flag
        if (!*error_flag) CheckEndOperators(array, error_flag);  // 7 flag также пустую строку, не бага а фича
        if (!*error_flag) CheckEmptyBrackets(array, error_flag);     // 8 flag (   )()
        if (!*error_flag) CheckMultipleDots(array, error_flag);      // 9 two dots in digit 1.2.3
        if (!*error_flag) CheckIsValidCharInput(array, error_flag);  // 10 flag (   )()
        if (!*error_flag) FindAndReplaceSpases(array, temp_array);
        if (!*error_flag) CopyArray(temp_array, array); */

    char *temp_array = MakeSameSizeArray(&array);
    if (!*error_flag) CheckEmptyArr(temp_array, error_flag);  // 1 flag not NULL

    MakeArrLower(array);                      // lowercase for all
    CheckBrackets(array, error_flag);         // 3 || 4 flag
    CheckDowbleOperators(array, error_flag);  // 5 flag
    CheckStartOperators(array, error_flag);   // 6 flag
    CheckEndOperators(array, error_flag);  // 7 flag также пустую строку, не бага а фича
    CheckEmptyBrackets(array, error_flag);     // 8 flag (   )()
    CheckMultipleDots(array, error_flag);      // 9 two dots in digit 1.2.3
    CheckIsValidCharInput(array, error_flag);  // 10 flag (   )()
    FindAndReplaceSpases(array, temp_array);
    CopyArray(temp_array, array);

    // DebugPrintArr(array, temp_array);
    free(temp_array);
    return array;
}

void FindAndReplaceSpases(char *source, char *dest) {
    while (*source) {
        while (Is_Space(*source)) {
            *dest++ = *source++;
        }
        if (Is_Bracket(*source) || Is_Operator(*source) || Is_X(*source)) {
            *dest++ = ' ';
            *dest++ = *source++;
            *dest++ = ' ';
            // source++;
        }
        *dest++ = *source++;
    }
    *dest++ = '\0';  //???
}

void CheckEmptyArr(const char *array, int *error_flag) {
    if (array == NULL) *error_flag = 1;
}

void CheckArrLenth(char *array, int *error_flag) {
    size_t length = strlen(array);
    if (length == 0) *error_flag = 2;
}

void MakeArrLower(char *array) {
    while (*array != '\0') {
        if (*array >= 'A' && *array <= 'Z') {
            *array += ('a' - 'A');
        }
        array++;
    }
}

char *MakeSameSizeArray(char **array) {
    size_t current_length = strlen(*array) + 1;
    char *new_array = (char *)malloc(current_length);
    for (size_t i = 0; i < current_length; i++) {
        new_array[i] = ' ';
    }
    new_array[current_length] = '\0';
    return new_array;
}

void MakeMyArrayBigger(char **array) {
    size_t currentLength = strlen(*array);
    size_t newLength = currentLength * 3;
    char *new_array = realloc(*array, newLength);
    *array = new_array;
}

void CheckBrackets(char *str, int *error_flag) {
    int count = 0;
    while (*str && !*error_flag) {
        if (*str == '(') {
            count++;
        } else if (*str == ')') {
            count--;
            if (count < 0) {
                *error_flag = 3;
            }
        }
        str++;
    }
    if (count != 0) {
        *error_flag = 4;
    }
}

void CheckDowbleOperators(char *str, int *error_flag) {
    char previous_char = '\0';
    while (*str) {
        if (Is_Space(*str)) {
            str++;
            continue;
        }
        if (Is_Operator(*str)) {
            if (Is_Operator(previous_char)) {
                *error_flag = 5;
                return;
            }
        }
        previous_char = *str;
        str++;
    }
}

void CheckStartOperators(char *str, int *error_flag) {
    while (*str && IsValidStart(*str)) {
        while (Is_Space(*str)) {
            str++;
        }
        if (Is_Operator(*str) && *str != '-') {
            *error_flag = 6;
            return;
        }
        str++;
    }
}

void CheckEndOperators(char *str, int *error_flag) {
    while (*str) {
        str++;
    }
    while (*str > 0 && Is_Space(*(str - 1))) {
        str--;
    }
    if (!IsValidEnd(*(str - 1))) {
        *error_flag = 7;
        return;
    }
    // str--;
}

void CheckEmptyBrackets(char *str, int *error_flag) {
    while (*str) {
        if (*str == '(') {
            str++;
            while (Is_Space(*str)) {
                str++;
            }
            if (*str == ')') {
                *error_flag = 8;
                return;
            }
        }
        str++;
    }
}

void CheckMultipleDots(char *str, int *error_flag) {
    while (*str) {
        if (Is_Digit(*str)) {
            int dot_count = 0;
            while (Is_Digit(*str)) {
                str++;
            }
            while (*str && (*str == '.' || Is_Digit(*str))) {
                if (Is_Dot(*str)) {
                    dot_count++;
                    if (dot_count > 1) {
                        *error_flag = 9;
                        return;
                    }
                }
                str++;
            }
        }
        str++;
    }
}

void CopyArray(char *source, char *dest) {
    while (*source) {
        *dest++ = *source++;
    }
    *dest = '\0';
}

void CheckIsValidCharInput(char *str, int *error_flag) {
    while (*str) {
        if (!IsValidCharInput(*str)) {
            *error_flag = 10;
            return;
        }
        str++;
    }
}

int Is_Letter(char ch) { return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); }
int Is_ValidChar(char ch) {
    return (ch == 'a' || ch == 'c' || ch == 'g' || ch == 'i' || ch == 'l' || ch == 'n' || ch == 'o' ||
            ch == 'q' || ch == 'r' || ch == 's' || ch == 't');
}
int Is_Digit(char ch) { return ch >= '0' && ch <= '9'; }
int Is_Dot(char ch) { return ch == '.'; }
int Is_Bracket(char ch) { return ch == '(' || ch == ')'; }
int Is_Operator(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'; }
int Is_Space(char ch) { return ch == ' '; }
int Is_X(char ch) { return ch == 'x'; }

int IsValidStart(char ch) { return Is_Letter(ch) || Is_Digit(ch) || Is_Bracket(ch) || ch == '-'; }
int IsValidEnd(char ch) { return Is_Letter(ch) || Is_Digit(ch) || ch == ')' || Is_Dot(ch); }
int IsValidCharInput(char ch) {
    return Is_ValidChar(ch) || Is_Digit(ch) || Is_Dot(ch) || Is_Bracket(ch) || Is_Operator(ch) ||
           Is_Space(ch) || Is_X(ch);
}

/* void DebugPrintArr(char *source, char *dest) {
    size_t length_source = strlen(source);
    size_t length_dest = strlen(dest);
    printf("Длина строки in: %zu Длина строки in:%zu\n", length_source, length_dest);
    for (size_t i = 0; i <= length_source; i++) {
        printf("%c", source[i]);
    }
    printf("\n");
    for (size_t i = 0; i <= length_source; i++) {
        printf("%c", dest[i]);
    }
} */
