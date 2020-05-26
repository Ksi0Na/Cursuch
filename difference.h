#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include "picture.h"
#include "alphabet.h"

typedef struct _Difference
{
    char symbol;
    double module_sum;
    double **coef;

} Difference;

void get_difference(int count, int new_M, int new_N,
                                Alphabet_new* alphabet, double*** matrix_NxM);


#endif // DIFFERENCE_H
