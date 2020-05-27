#include <stdio.h>
#include "difference.h"
#include <stdlib.h>

int main()
{
    COEF* coef = work_with_file_matrix();
    AC* ASCII_column = work_with_alphabet();
    differences(ASCII_column, coef);
    
    return 0;
}
