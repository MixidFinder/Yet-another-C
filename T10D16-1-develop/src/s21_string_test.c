#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

void s21_strlen_test(char *inp, int exp);
void s21_strcmp_test(char *inp, char *inp_two, int exp);
void s21_strcpy_test(char *inp, char *source, int exp);

int main(void) {
#ifdef Quest_1
    s21_strlen_test("12345", 5);
    s21_strlen_test("", 0);
    s21_strlen_test("123 45", 6);
    s21_strlen_test("1", 1);
    s21_strlen_test("   ", 3);
    s21_strlen_test(NULL, 4);
#endif

#ifdef Quest_2
    s21_strcmp_test("123", "123", 0);
    s21_strcmp_test("1234", "123", 52);
    s21_strcmp_test("123", "1234", -52);
    s21_strcmp_test(NULL, "1234", 0);
#endif

#ifdef Quest_3
    char *test_str = "";
    s21_strcpy_test(test_str, "12345", 0);
    test_str = "     ";
    s21_strcpy_test(test_str, "1", 0);
    test_str = "1";
    s21_strcpy_test(test_str, "12345", 0);
    test_str = "23232323232323";
    s21_strcpy_test(test_str, "666666", 0);
    test_str = NULL;
    s21_strcpy_test(test_str, "12345", 0);
    test_str = "1";
    s21_strcpy_test(test_str, NULL, 1);
#endif

    return 0;
}

void s21_strlen_test(char *inp, int exp) {
    int res = s21_strlen(inp);
    char *suc = "SUCCESS\n";
    char *fail = "FAIL\n";
    printf("%s %d %s", inp, exp, exp == res ? suc : fail);
}

void s21_strcmp_test(char *inp, char *inp_two, int exp) {
    int res = s21_strcmp(inp, inp_two);
    char *suc = "SUCCESS\n";
    char *fail = "FAIL\n";
    printf("%s %d %s", inp, exp, exp == res ? suc : fail);
}

void s21_strcpy_test(char *inp, char *source, int exp) {
    inp = s21_strcpy(source);
    char *suc = "SUCCESS\n";
    char *fail = "FAIL\n";
    printf("%s %d %s", inp, exp, s21_strcmp(inp, source) == exp ? suc : fail);
    free(inp);
}