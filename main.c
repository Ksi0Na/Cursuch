#include <stdio.h>
#include "picture.h"
#include <stdlib.h>

int main()
{
    FILE *f;
    //---------------------get_memory_for_way---------------------
    char* way = request_way();
    //---------------------get_memory_for_way---------------------
    f = fopen(way, "rb");/////////////////////////////
    if (check_open_file(way, f)) main();

    if ( file_type_check(f, way)) {
        fclose(f);////////////////////////////////////
        main();
    } 
    
    free(way);
    //======================================
    int width = get_width(f);
    int height = get_height(f);
    
     RGB **matrix = do_RGB(f);
    
    fclose(f);/////////////////////////////////////
    //======================================
    int N = 20;
    int M = 13;
    
    int new_width = get_new_width(width, M);
    int new_height = get_new_height(height, N);
    
    int** m = do_BW_matrix(new_height, new_width,
                                           height, width, matrix);

    delete_RGB(matrix, height);
    //======================================     
    unsigned int count = new_height * new_width / (N * M);    
    
     double*** matrix_NxM = do_matrix_NxM(count, N, M,
                         new_height, new_width, m);

    
    return 0;
}
