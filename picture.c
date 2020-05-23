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
    {
        type[i] = fgetc(f);
    }

    if (type[0] != 'B' || type[1] != 'M')
    {
        printf("-------------------------------------------------------------------------------------\n");
        printf("Error: It's not bmp file\n");
        printf("-------------------------------------------------------------------------------------\n");
        return 1;
    }
    return 0;
}

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
void get_RGB_matrix(int height, int width, RGB** matrix,  FILE *f)
{
    int bytes;
    fseek(f, 34, 0);
    fread(&(bytes), 4, 1, f);
    bytes = bytes / (height * width);
    if (bytes == 4)
    {
        fseek(f, 54, 0);
        for (int i = 0; i != height; i++)
        {
            for (int j = 0; j != width; j++)
            {
                matrix[i][j].red = fgetc(f);
                matrix[i][j].green = fgetc(f);
                matrix[i][j].blue = fgetc(f);
                fgetc(f);
            }
        }
    }   
    else 
    {
        fseek(f, 54, 0);
        for (int i = 0; i != height; i++)
        {
            for (int j = 0; j != width; j++)
            {
                matrix[i][j].red = fgetc(f);
                matrix[i][j].green = fgetc(f);
                matrix[i][j].blue = fgetc(f);
            }
        }
    }
}

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
void do_white(int new_height, int new_width, BW** m)
{
    for (int i = 0; i < new_height; i++)
    {
        for (int j = 0; j < new_width; j++)
        {
            m[i][j].darkness = 255;
        }
    }
}
void get_BW_matrix(int height, int width, BW** m, RGB **matrix)
{
    for (int i = 0; i != height; i++)
    {
        for (int j = 0; j != width; j++)
        {
            if(!(matrix[i][j].red + matrix[i][j].green + matrix[i][j].blue)) m[i][j].darkness = 0;
            m[i][j].darkness = (matrix[i][j].red + matrix[i][j].green + matrix[i][j].blue) / 3;
        }
    }
}

