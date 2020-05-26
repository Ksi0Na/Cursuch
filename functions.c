#include "functions.h"

int all()
{
    FILE *f;
    //---------------------get_memory_for_way---------------------------
    char* way = request_way();
    //---------------------get_memory_for_way---------------------------
    f = fopen(way, "rb");////////////////////////////////////
    if (check_open_file(way, f)) all();

    if ( file_type_check(f, way)) {
        fclose(f);//////////////////////////////////////////
        all();
    } 
    
    free(way);
    //=============================================
    int width = get_width(f);
    int height = get_height(f);
    
     RGB **matrix = do_RGB(f);
    
    fclose(f);////////////////////////////////////////////
    //=============================================   
    int N = 20;
    int M = 13;
    
    int new_width = get_new_width(width, M);
    int new_height = get_new_height(height, N);
    
    int** m = do_BW_matrix(new_height, new_width,
                                           height, width, matrix);

    delete_RGB(matrix, height);
    //=============================================      

//    int*** matrix_NxM;
//    unsigned int count = new_height * new_width / (N * M);    
//     //---------------get_memory_for_BW_matrixs_3x4------------------
//    matrix_NxM = (int ***)calloc(M, sizeof(unsigned int **));
//    for(int i = 0; i < M; i++)
//    {
//        matrix_NxM[i] = (int **)calloc(N, sizeof(int *));
//        for(unsigned int j = 0; j < N; j++)
//        {
//            matrix_NxM[i][j] = (int *)calloc(count, sizeof(int ));
//        }
//    }
//    //---------------get_memory_for_BW_matrixs_3x4------------------
//    //get_BW_matrix_NxM(new_width, new_height, count, N, M, matrix_NxM, m);
//    //print_BW_matrix_NxM(M, N, count, matrix_NxM);
    
    delete_BW(m, new_height);
    
//    free (matrix_NxM);
    
    return 0;
} 
