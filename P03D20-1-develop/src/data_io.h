#ifndef DATA_INP_OUTP_H
#define DATA_INP_OUTP_H

#define LEN_X 80
#define LEN_Y 25
#define EMPTY '.'
#define FILLED '*'

char *Input(void);
void Output(char **matr);
void DebugPrint(int error_flag);
char **CreateDynamic2dArray(int *is_valid_input);
void Clear2dArr(char **array);
void ClearMyScreen();

#endif