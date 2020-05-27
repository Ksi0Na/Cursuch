#include "difference.h"

Difference* get_memory_diff_m(COEF*coef)
{
    Difference* diff = malloc(sizeof (Difference));
    
    diff->coef = (double***)calloc(coef->c, sizeof (unsigned int**));
    for(unsigned i =0; i < coef->c; i++)
    {
        diff->coef[i] = (double**)calloc(coef->h, sizeof (int*));
        for(int j =0; j < coef->h; j++)
        {
            diff->coef[i][j] = (double*)calloc(coef->w, sizeof (int));
        }
    }
    
    diff->module_sum = malloc(sizeof (double));
    diff->symbol = malloc(sizeof (char));
    
    return diff;
}


void get_difference(AC* alphabet, COEF* coef)
{
    Difference* diff = get_memory_diff_m(coef);
    
    for (int v = 0; v < 95; v++)
        for (unsigned p = 0; p < coef->c; p++)
            for(int i = 0; i < coef->h; i++)
                for (int j = 0; j < coef->w; j++)
                {
                    
                }
}
