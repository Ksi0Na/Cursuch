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
    int w;
    int h;
    unsigned c;

} Difference;

typedef struct _Result
{
    char** symbol;
    unsigned N;
    unsigned M;
} Result;

Difference* get_memory_diff_m(COEF*);
void get_difference(AC*, COEF*, Difference*);
void delete_diff_m(Difference*);

Result* get_memory_res_m(COEF*);
void get_result(Difference*, COEF*, Result*);
void delete_res_m(Result*);

void print_art(Result*);
void differences(AC*, COEF*);

#endif // DIFFERENCE_H
