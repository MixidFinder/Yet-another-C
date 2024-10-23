#include <stdlib.h>

#include "data_io.h"
#include "data_parse.h"
#include "polish_notation.h"

// name convention for functions CamelCase
// name convention for variables snake_case

int main() {
    int error_flag = 0;  // 0 is ok 1 or upper if mistake
    char *input_string_arr = Input();
    input_string_arr = ParseCharArr(input_string_arr, &error_flag);  //вернет новый указатель
    char **grapf_logic_arr = CreateDynamic2dArray(&error_flag);
    if (grapf_logic_arr != NULL) FillLogicArr(input_string_arr, grapf_logic_arr, &error_flag);

    if (error_flag) DebugPrint(error_flag);

    free(input_string_arr);
    free(grapf_logic_arr);

    return 0;
}
