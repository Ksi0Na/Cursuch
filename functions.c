#include "functions.h"

int all()
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
    
    //=============================================
    //=============================================   

    RGB **matrix; 
    int width = get_width(f);
    int height = get_height(f);
    //---------------get_memory_for_RGB_matrix------------------------
    matrix = (RGB **)calloc(height, sizeof(int *));
    for(int i = 0; i < height; i++)
    {
        matrix[i] = (RGB *)calloc(width, sizeof(int *));
    }
    //---------------get_memory_for_RGB_matrix------------------------
    get_RGB_matrix(height, width, matrix, f);        
    
    fclose(f);////////////////////////////////////////////
    //=============================================
    //=============================================   
    int N = 20;
    int M = 13;
    
    int new_width = get_new_width(width, M);
    int new_height = get_new_height(height, N);
    
    BW** m;
    //---------------get_memory_for_BW_matrix-------------------------
    m = (BW **)calloc(new_height, sizeof(int *));
    for(int i = 0; i < new_height; i++)
    {
        m[i] = (BW *)calloc(new_width, sizeof(int *));
    }
    //---------------get_memory_for_BW_matrix-------------------------
    do_white(new_height, new_width, m);
    get_BW_matrix(height, width, m, matrix);     
    //--------------free_memory_for_RGB_matrix------------------------
    for(int i = 0; i < height; i++)     free(matrix[i]);
    free(matrix);
    //--------------free_memory_for_RGB_matrix------------------------
    
    //=============================================
    //=============================================       

//    BW*** matrix_NxM;
//    int count = new_height * new_width / (N * M);    
//     //---------------get_memory_for_BW_matrixs_3x4------------------
//    matrix_NxM = (BW ***)calloc(M, sizeof(unsigned int **));
//    for(int i = 0; i < M; i++)
//    {
//        matrix_NxM[i] = (BW **)calloc(N, sizeof(int *));
//        for(unsigned int j = 0; j < N; j++)
//        {
//            matrix_NxM[i][j] = (BW *)calloc(count, sizeof(int ));
//        }
//    }
//    //void do_memory_for_3D_matrix(h, w, count, m);
//    //---------------get_memory_for_BW_matrixs_3x4------------------
//    //get_BW_matrix_NxM(new_width, new_height, count, N, M, matrix_NxM, m);
//    //print_BW_matrix_NxM(M, N, count, matrix_NxM);
    
    //--------------free_memory_for_BW_matrix-------------------------
    for(int i = 0; i < new_height; i++)     free(m[i]);
    free(m);
    //--------------free_memory_for_BW_matrix-------------------------
    
//    free (matrix_NxM);
    
    return 0;
} 
