#ifndef ASCII_ART_H
#define ASCII_ART_H

#include "difference.h"

typedef struct _Art
{
        char ** image;
} Art;

void ASCII_art(Difference*);
void print_art(Art);

#endif // ASCII_ART_H
