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

void get_difference(AC* alphabet, COEF* coef, Difference* diff)
{
    diff->c = coef->c;
    diff->h = coef->h;
    diff->w = coef->w;
    
    double c = 0, c1 = 0, c2 = 0;
    for (int v = 0; v < 95; v++)
    {
        for (unsigned p = 0; p < coef->c; p++)
        {
            for(int i = 0; i < coef->h; i++)
            {
                for (int j = 0; j < coef->w; j++)
                {
                    modf(coef->m[p][i][j], &c1);
                    c2 = nearbyint((coef->m[p][i][j] - c1) * 100) * 0.01;
                    c = c1 + c2;
                    coef->m[p][i][j] = c;
                    
                    for(; coef->m[p][i][j] == alphabet[v].matrix[i][j];)
                    {
                        if (coef->m[p][i][j] < alphabet[v].matrix[i][j])
                        {
                            diff->coef[p][i][j] +=0.01;
                            coef->m[p][i][j] += 0.01;
                        }
                        if (coef->m[p][i][j] > alphabet[v].matrix[i][j])
                        {
                            diff->coef[p][i][j] -=0.01;
                            coef->m[p][i][j] -= 0.01;
                        }
                    }
                    
                    diff->module_sum[p] += diff->coef[p][i][j];
                }
            }
            diff->symbol[p] = alphabet[v].symbol;
            
            diff->module_sum[p] /= (coef->h * coef->w);
            diff->module_sum[p] = fabs(diff->module_sum[p]);
        }
    }
}

void delete_diff_m(Difference* diff)
{
    free(diff->symbol);
    free(diff->module_sum);
    
    for(unsigned i =0; i < diff->c; i++)
    {
        for(int j =0; j < diff->h; j++)
        {
            free(diff->coef[i][j]);
        }
        free(diff->coef[i]);
    }
    free(diff->coef);
    
    free(diff);
}

Result* get_memory_res_m(COEF* coef)
{
    Result* res = malloc(sizeof(Result*));
       
    res->symbol = (char**)calloc(coef->n_h, sizeof(int *));
     for(int i = 0; i < coef->n_h; i++)
     {
        res->symbol[i] = (char *)calloc(coef->n_w, sizeof(int *));
     }
    
    return res;
}

void get_result(Difference* diff, COEF* coef, Result* res)
{
    res->N = coef->n_h;
    res->M = coef->n_w;
    
    int index = 0;
    unsigned i = 0, j = 0;
    for (int v = 0; v < 95; v++)
    {
        for (unsigned p = 0; p < diff->c; p++)
        {
            if (diff->module_sum[p] <= diff->module_sum[index])
                index = p;
        }
        res->symbol[i][j] = diff->symbol[index];
        j++;
        if(j > res->M)
        {
            j = 0; i++; 
        }
    }
}

void delete_res_m(Result* res)
{
    for(unsigned i = 0; i < res->N; i++)
        free(res->symbol[i]);
    
    free(res);
}

void print_art(Result* res)
{
    for (unsigned i = 0; i < res->N; i++)
    {
        for(unsigned j = 0; j < res->M; j++)
        {
            printf("%c", res->symbol[i][j]);
        }
        printf("\n");
    }   
}

void differences(AC* alphabet, COEF* coef)
{
    Difference* diff = get_memory_diff_m(coef);
    get_difference(alphabet, coef, diff);
    
    delete_AC(alphabet);
    
    Result* res = get_memory_res_m(coef);
    get_result(diff, coef, res);
    
    delete_COEF(coef);
    
    print_art(res);
    
    delete_res_m(res);
}
