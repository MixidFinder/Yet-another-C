#ifndef DATA_PARSE_H
#define DATA_PARSE_H

char *ParseCharArr(char *array, int *error_flag);

void CheckEmptyArr(const char *array, int *error_flag);
void CheckArrLenth(char *array, int *error_flag);
void MakeArrLower(char *array);
void CheckBrackets(char *str, int *error_flag);
void CheckDowbleOperators(char *str, int *error_flag);
void CheckStartOperators(char *str, int *error_flag);
void CheckEndOperators(char *str, int *error_flag);
void CheckEmptyBrackets(char *str, int *error_flag);
void CheckMultipleDots(char *str, int *error_flag);
void CheckIsValidCharInput(char *str, int *error_flag);
void FindAndReplaceSpases(char *source, char *dest);

char *MakeSameSizeArray(char **array);
void MakeMyArrayBigger(char **array);
void CopyArray(char *source, char *dest);

int Is_Letter(char ch);
int Is_ValidChar(char ch);
int Is_Digit(char ch);
int Is_Dot(char ch);
int Is_Bracket(char ch);
int Is_Operator(char ch);
int Is_Space(char ch);
int Is_X(char ch);

int IsValidStart(char ch);
int IsValidEnd(char ch);
int IsValidChar(char ch);
int IsValidCharInput(char ch);

// void DebugPrintArr(char *source, char *dest);

#endif