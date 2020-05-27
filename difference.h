#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include "picture.h"
#include "alphabet.h"

//95

typedef struct _Difference
{
    char *symbol;
    double *module_sum;
    double ***coef;

} Difference;

typedef struct _Result
{
    char** symbol;
    unsigned N;
    unsigned M;
} Result;

Difference* get_memory_diff_m(COEF*);
void get_difference(AC* alphabet, COEF* coef);



#endif // DIFFERENCE_H
