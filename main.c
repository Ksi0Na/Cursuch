#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structs.h"
#include "Header.h"

int main()
{
    FILE *f;
    //---------------------get_memory_for_way---------------------------
    char* way = request_way();
    //---------------------get_memory_for_way---------------------------

    f = fopen(way, "rb");////////////////////////////////////
    if (check_open_file(way, f)) main();
    free(way);

    if ( file_type_check(f)) 
    {
        free(way);
        fclose(f);//////////////////////////////////////////
        main();
    } 
    unsigned int width = get_width(f);
    unsigned int height = get_height(f);

    RGB **matrix; 
    //---------------get_memory_for_RGB_matrix------------------------
    matrix = (RGB **)calloc(height, sizeof(unsigned int *));
    for(unsigned int i = 0; i < height; i++)
    {
        matrix[i] = (RGB *)calloc(width, sizeof(unsigned int *));
    }
    //---------------get_memory_for_RGB_matrix------------------------
    get_RGB_matrix(height, width, matrix, f);        
    //print_RGB_matrix(height, width, matrix);
    //print_RGB_matrix_in_file(height, width, f);
    fclose(f);////////////////////////////////////////////

    BW** m;
    unsigned int new_width = width;
    unsigned int new_height = height;
    while (new_height % 4) new_height += 1;
    while (new_width  % 3)  new_width  += 1;
    //---------------get_memory_for_BW_matrix-------------------------
    m = (BW **)calloc(new_height, sizeof(unsigned int *));
    for(unsigned int i = 0; i < new_height; i++)
    {
        m[i] = (BW *)calloc(new_width, sizeof(unsigned int *));
    }
    //---------------get_memory_for_BW_matrix-------------------------
    do_white(new_height, new_width, m);
    get_BW_matrix(height, width, m, matrix);     
    free (matrix);
    print_BW_matrix(new_height, new_width, m);   

    
//
//    free (matrix);
    free (m);
    
    
    return 0;
}
