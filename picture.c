#include "picture.h"

int check_open_file(char* way, FILE *f)
{
    
    if (!f) 
    {
        free (way);
        printf("-------------------------------------------------------------------------------------\n");
        printf("Error: File not open\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("Try again\n");
        getchar();
        return 1;
    }
    return 0;
}

int read_number(int begin, int end)
{
    int number;
    int real_read_count = scanf("%d", &number);
    while ((real_read_count == 0) || !((begin <= number) && (number <= end))) {
        char c;
        while ((c = getchar()) != '\n');
        printf("You must enter number from %d to %d: ", begin, end);
        real_read_count = scanf("%d", &number);
    }
    return number;
}
char* smart_str()
{
    char* way = (char*)malloc(sizeof(char));
    way[0] = '\0';
    char s = getchar();
    while (s != '\n')
    {
        way = (char*)realloc(way, sizeof(char) * (strlen(way) + 2));
        strncat(way, &s, 1);
        s = getchar();
    }
    return way;
}
char* request_way()
{
    printf("==================================================\n");
    printf("Enter the path to the file:\n");
    char* way = smart_str();

    int choise;
    printf("==================================================\n");
    printf("Introduced: %s\n", way);
    printf("==================================================\n");
    printf("[0] continure\n");
    printf("[1] repeat the input\n\n");
    choise = read_number(0, 1);
    printf("==================================================\n");
    
    if (choise) 
    { 
        free (way);
        getchar();
        request_way(); 
    }
    return way;
}
int file_type_check(FILE *f)
{
    rewind(f);
    char type[2];
    for (int i = 0; i != 2; i++) 
        type[i] = fgetc(f);


    if (type[0] != 'B' || type[1] != 'M')
    {
        printf("-------------------------------------------------------------------------------------\n");
        printf("Error: It's not bmp file\n");
        printf("-------------------------------------------------------------------------------------\n");
        return 1;
    }
    return 0;
}
/////////////////////////////////////////
int get_width(FILE *f)
{
    int width;
    fseek(f, 18, 0);
    fread(&(width), 4, 1, f);
    return width;
}
int get_height(FILE *f)
{
    int height;
    fseek(f, 22, 0);
    fread(&(height), 4, 1, f);
    return height;
}

void get_RGB_matrix(int height, int width, RGB* matrix,  FILE *f)
{
    matrix->width = width;
    matrix->height = height;
    
    int bytes;
    fseek(f, 34, 0);
    fread(&(bytes), 4, 1, f);
    bytes = bytes / (height * width);
    if (bytes == 4)
    {
        fseek(f, 54, 0);
        for (int i = 0; i !=  matrix->height; i++)
        {
            for (int j = 0; j !=  matrix->width; j++)
            {
                matrix->red[i][j] = fgetc(f);
                matrix->green[i][j] = fgetc(f);
                matrix->blue[i][j] = fgetc(f);
                fgetc(f);
            }
        }
    }   
    else 
    {
        fseek(f, 54, 0);
        for (int i = 0; i !=  matrix->height; i++)
        {
            for (int j = 0; j !=  matrix->width; j++)
            {
                matrix->red[i][j] = fgetc(f);
                matrix->green[i][j] = fgetc(f);
                matrix->blue[i][j] = fgetc(f);
            }
        }
    }
}
RGB* memory_RGB(int height, int width)
{
   RGB *matrix = malloc(sizeof(RGB));
      
   matrix->red = (int**)calloc(height, sizeof(int *));
    for(int i = 0; i < height; i++)
    {
       matrix->red[i] = (int *)calloc(width, sizeof(int *));
    }
    
    matrix->green = (int**)calloc(height, sizeof(int *));
    for(int i = 0; i < height; i++)
    {
        matrix->green[i] = (int *)calloc(width, sizeof(int *));
    }
    
    matrix->blue = (int**)calloc(height, sizeof(int *));
    for(int i = 0; i < height; i++)
    {
        matrix->blue[i] = (int *)calloc(width, sizeof(int *));
    }
    
    return matrix;
}
void delete_RGB(RGB* matrix)
{
    for (int i = 0; i <  matrix->height; i++)
    {
        free(matrix->red[i]);
        free(matrix->green[i]);
        free(matrix->blue[i]);
    }
    free(matrix);
}
/////////////////////////////////////////
int get_new_width(int width, int M)
{
    int new_width = width;
    while (new_width  % M)  new_width  += 1;
    return new_width;
}
int get_new_height(int height, int N)
{
    int new_height = height;
    while (new_height  % N)  new_height  += 1;
    return new_height;
}

void do_white(BW* m)
{
    for (int i = 0; i < m->h; i++)
    {
        for (int j = 0; j < m->w; j++)
        {
            m->m[i][j] = 255;
        }
    }
}
BW* memory_BW(int new_height, int new_width)
{
   BW *m = malloc(sizeof(BW));
      
   m->m = (int**)calloc(new_height, sizeof(int *));
    for(int i = 0; i < new_height; i++)
    {
       m->m[i] = (int *)calloc(new_width, sizeof(int *));
    }
    
    return m;
}
void get_BW_matrix(int new_height, int new_width, RGB* matrix, BW* m)
{
    m->h = new_height;
    m->w = new_width;
    
    do_white(m);
    
    for(int i = 0; i < matrix->height; i++)
        for(int j = 0; j < matrix->width; j++)
            m->m[i][j] = (matrix->red[i][j] + matrix->blue[i][j] + matrix->green[i][j]) /3;
}
int get_BW_m(BW* m, int h, int w)
{
    return m->m[h][w];
}
void delete_BW(BW* m)
{
    for(int i = 0; i < m->h; i++)     free(m->m[i]);
    free(m);
}
/////////////////////////////////////////
COEF* memory_COEF(unsigned int count, int new_height, int new_width)
{
    COEF* coef = malloc(sizeof (COEF));
    
    coef->m = (double***)calloc(count, sizeof (unsigned int**));
    for(unsigned i =0; i < count; i++)
    {
        coef->m[i] = (double**)calloc(new_height, sizeof (int*));
        for(int j =0; j < new_height; j++)
        {
            coef->m[i][j] = (double*)calloc(new_width, sizeof (int));
        }
    }
    
    return coef;
}
void get_coef(COEF* coef)
{
    for(unsigned int i = 0; i < coef->c; i++)
        for(int j = 0; j < coef->h; j++)
            for(int k = 0; k < coef->w; k++)
                coef->m[i][j][k] /= 255 ;
}
void get_COEF_matrix(unsigned int count, int N, int M, BW* m, COEF* coef)
{
    coef->c = count;
    coef->h = N;
    coef->w = M;
    
    int h = 0, w = 0;
    for (unsigned int c = 0; c < coef->c; c++)
        for (int b = 0; b < coef->h; b++)
            for (int a = 0; a < coef->w; a++)
            {
                set_COEF_m(coef, c, b, a, get_BW_m(m, h, w));
                w++;
                if(w > m->w)
                {
                    w =0; h++;
                }
            }
    get_coef(coef);
}
void set_COEF_m(COEF* coef, unsigned c, int b, int a, int value)
{
    coef->m[c][b][a] = value;
}
void delete_COEF(COEF* coef)
{
    for(unsigned i = 0; i < coef->c; i++)
        for(int j = 0; j < coef->h; j++)
            free(coef->m[i][j]);
    free(coef);
}

COEF* work_with_file_matrix()
{
    FILE *f;
    //---------------------get_memory_for_way---------------------
    char* way = request_way();
    //---------------------get_memory_for_way---------------------
    f = fopen(way, "rb");/////////////////////////////
    if (check_open_file(way, f)) work_with_file_matrix();
    
    free(way);
    
    if ( file_type_check(f)) {
        fclose(f);////////////////////////////////////
        work_with_file_matrix();
    } 
    //======================================
    int width = get_width(f);
    int height = get_height(f);
    
    RGB* matrix = memory_RGB(height, width);
    get_RGB_matrix(height, width, matrix, f);  
     
    fclose(f);/////////////////////////////////////
    //======================================
    int N = 20;
    int M = 13;
    
    int new_width = get_new_width(width, M);
    int new_height = get_new_height(height, N);
    
    BW* m = memory_BW(new_height, new_width);
    get_BW_matrix(new_height, new_width, matrix, m);  

     delete_RGB(matrix);
    //======================================     
    unsigned int count = new_height * new_width / (N * M);   
    N *= M; M= 1;
    
    COEF* coef = memory_COEF(count, new_height, new_width);
    get_COEF_matrix(count, new_height, new_width, m, coef);  

    delete_BW(m);
    
    return coef;
}
