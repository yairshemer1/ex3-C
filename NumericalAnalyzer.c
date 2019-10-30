//
// Created by Yair Shemer on 21/08/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "infi.h"
/**
 * returns 1 if the number is a positive integer, 0 otherwise.
 */
#define IS_INT_POS(a) ((((double) (int) a) == a) && a > 0)

#define USAGE_ERROR fprintf(stderr, \
"Usage:  NumericalAnalyzer <function number> <a> <b> <N> <x0> <h>\n"); return EXIT_FAILURE;

#define INVALID_ERROR fprintf(stderr, "Invalid input\n"); return EXIT_FAILURE;

#define NUM_OF_FUNCS 6

static const int ARGS_NUM = 7;

static const int FUNC_LOC = 1;

static const int X0_LOC = 5;

static const int H_LOC = 6;

static const int N_LOC = 4;

static const int INVALID = -1;

static const int A_LOC = 2;

static const int B_LOC = 3;

/**
 * The following 6 functions are the given functions. Variable x is the input, the return
 * value is f(x), for each of the given functions.
 */

double f1(double x)
{
    return (pow(x, 2) / 4);
}

double f2(double x)
{
    return ((-1 * pow(x, 3) + 3 * pow(x, 2) + x - 4 * sqrt(x)) / (2 * x * sqrt(x)));
}

double f3(double x)
{
    return (pow(sin(x), 2) - pow(cos(x), 2));
}

double f4(double x)
{
    return (sin(x) / (1 + cos(2 * x)));
}

double f5(double x)
{
    return pow(M_E, x);
}

double f6(double x)
{
    return (sinh(2 * x) / (M_E * pow(x, 2)));
}

/**
 * global variable representing an error
 */
int parsingDoubleError;

/**
 * This function will parse a string into a double. If an error was detected, the global variable
 * 'parsingDoubleError' will change it's value.
 * @param str string to parse
 * @return numeric value
 */
double readNum(char *str)
{
    char *strEnd;
    double value = strtod(str, &strEnd);
    if (strlen(strEnd) != 0)
    {
        parsingDoubleError = INVALID;
        return 0;
    }
    return value;
}

int main(int argc, char *argv[])
{
    if (argc != ARGS_NUM)
    {
        USAGE_ERROR
    }
    //reading the values into the variables and parsing it
    double funcNum = readNum(argv[FUNC_LOC]), x0 = readNum(argv[X0_LOC]), h = readNum(argv[H_LOC]);
    double a = readNum(argv[A_LOC]), b = readNum(argv[B_LOC]), n_arg = readNum(argv[N_LOC]);
    if (!IS_INT_POS(funcNum) || funcNum > NUM_OF_FUNCS || !IS_INT_POS(n_arg) ||
        parsingDoubleError == INVALID || a >= b)
    {
        INVALID_ERROR
    }
    RealFunction funcArr[NUM_OF_FUNCS] = {f1, f2, f3, f4, f5, f6};
    int i = (int) funcNum - 1; //location of the function in the array
    //if function has not finite value around x0
    if (isnan(funcArr[i](x0 - h)) || isnan(funcArr[i](x0 + h)))
    {
        INVALID_ERROR
    }
    unsigned int n = (unsigned int) n_arg;
    //printing results
    printf("Integral: %0.5f\n", integration(funcArr[i], a, b, n));
    printf("Derivative: %0.5f\n", derivative(funcArr[i], x0, h));
    return EXIT_SUCCESS;
}
