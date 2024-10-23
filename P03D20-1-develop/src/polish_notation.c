#include "polish_notation.h"

#include "data_io.h"
#include "data_structure.h"

void FillLogicArr(char *array, char **logic_arr, int *error_flag) {
    t_dstack *polka = PolishNotation(array);
    double y_value = 0;
    ClearMyScreen();
    Clear2dArr(logic_arr);
    for (int i = 0; i < 80; i++) {
        *error_flag = Calculation(polka, (4 * M_PI * i / 79), &y_value);
        if (y_value >= -1 && y_value <= 1) {  // [-1, 1]
            double y_coord = round(((y_value + 1) * 12));
            logic_arr[(int)y_coord][i] = '*';
        }
    }
    if (*error_flag) {
        if (*error_flag & 1) printf("\nMATH ERROR: Divison by zero\n");
        if (*error_flag & 2) printf("\nMATH ERROR: Square Root of Negative\n");
    } else {
        Output(logic_arr);
    }
    FreeStack(polka);
}

double CalcBinar(char *oper, double a, double b) {
    double result = NAN;

    if (strstr("+", oper))
        result = a + b;
    else if (strstr("-", oper))
        result = a - b;
    else if (strstr("/", oper))
        result = a / b;
    else if (strstr("*", oper))
        result = a * b;
    else if (strstr("^", oper))
        result = pow(a, b);
    return result;
}

double CalcTrig(char *oper, double a) {
    double result = NAN;

    if (strstr("sin", oper))
        result = sin(a);
    else if (strstr("cos", oper))
        result = cos(a);
    else if (strstr("tan", oper))
        result = tan(a);
    else if (strstr("ctg", oper))
        result = pow(tan(a), -1);
    else if (strstr("sqrt", oper))
        result = sqrt(a);
    else if (strstr("ln", oper))
        result = log(a);
    return result;
}

int IsZero(char *token) { return (strstr("0 0.0 .0 .0000", token) != NULL); }

int IsBinar(char *oper) { return (oper && strstr("+-*/^", oper) != NULL); }

int IsTrig(char *oper) { return (oper && strstr("sin cos tan ctg sqrt ln", oper) != NULL); }

/*
    input: a stack with expression, an abcissa and pointer to ordinata
    CHECK WRONG MATHEMATICAL EXPRESSIONS:
    error code 0x001 -- null divisor;
    error code 0x010 -- sqrt(-1);
    STACK ERRORS:
    error code 0x100 -- wrong stack;
    output: 0 and y value if success OR an error code and NAN otherwise
*/
int Calculation(t_dstack *polka, double x, double *y) {
    double que[polka->top + 1];
    int last = -1;
    int err = 0;

    for (int i = 0; i <= polka->top && !err; ++i) {
        char *tok = polka->arr[i];
        double tmp = atof(tok);

        if (IsZero(tok) || tmp) {
            que[++last] = tmp;
        } else if ('X' == *tok || 'x' == *tok) {
            que[++last] = x;
        } else if (IsTrig(tok)) {
            double e = que[last--];

            if (strstr("sqrt", tok) && e < 0) {
                err |= 0x10;
            } else {
                que[++last] = CalcTrig(tok, e);
            }
        } else if (IsBinar(tok)) {
            double b = que[last--];
            double a = que[last--];

            if (strstr("/", tok) && b == 0) {
                err |= 0x1;
            } else {
                que[++last] = CalcBinar(tok, a, b);
            }
        }
    }
    if (last == 0 && err == 0) {
        *y = que[last--];
    } else {
        *y = NAN;
        err |= 0x100;
    }
    return err;
}

/*
    input: pointer to left and right operator
    [^], [* /], [+ -]; from greater to lower precedent respectevily
    output: 1 if has greater precedence or 0 otherwise
*/
int CmpOper(char *left, char *right) {
    char *abc = "()+-*/^";
    int p1 = (strchr(abc, *left) - abc) / 2;
    int p2 = (strchr(abc, *right) - abc) / 2;

    return (p1 >= p2) && !(p1 == 3 && p2 == 3);
}

/*
    input: "2 + sin( 8 + 9 * sin( cos( ln( 1 / -8 ) ) ) )"
    output: a que with polish notation
*/
t_dstack *PolishNotation(char *input) {
    t_dstack *stack = InitStack();
    t_dstack *que = InitStack();

    char *token = strtok(input, " ");
    for (; token != NULL; token = strtok(NULL, " ")) {
        if (IsZero(token) || atof(token) || 'X' == *token || 'x' == *token) {
            Push(que, token);
        } else if (strstr("(", token) || IsTrig(token)) {
            Push(stack, token);
        } else if (IsBinar(token)) {
            while (IsEmpty(stack) == 0 && CmpOper(Peek(stack), token)) {
                Push(que, Pop(stack));
            }
            Push(stack, token);
        } else if (strstr(")", token)) {
            while (IsEmpty(stack) == 0 && strstr("(", Peek(stack)) == NULL) {
                Push(que, Pop(stack));
            }
            Pop(stack);
            if (IsEmpty(stack) == 0 && IsTrig(Peek(stack))) {
                Push(que, Pop(stack));
            }
        }
    }
    while (IsEmpty(stack) == 0) {
        Push(que, Pop(stack));
    }
    FreeStack(stack);
    return que;
}
