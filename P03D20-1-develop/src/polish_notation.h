#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

#include "data_structure.h"

int Calculation(t_dstack *polka, double x, double *y);
t_dstack *PolishNotation(char *input);
void FillLogicArr(char *array, char **logic_arr, int *error_flag);

#endif