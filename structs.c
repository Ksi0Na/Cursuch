#include "structs.h"
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

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
unsigned int file_type_check(FILE *f)
{
    rewind(f);
    char type[2];
    for (unsigned int i = 0; i != 2; i++)
    {
        type[i] = fgetc(f);
    }

    if (type[0] != 'B' || type[1] != 'M')
    {
        printf("Error: It's not bmp file\n");
        return 1;
    }
    return 0;
}

void get_size_of_matrix(BitMap image, FILE *f)
{
    rewind(f);
    for (int i = 0; i != 18; i++)
    {                                       //now it is position of 18 bit
        printf("%d\n", fgetc(f));
        
    }
    image.width = fgetc(f);
    
     fgetc(f);fgetc(f);fgetc(f);
     
     image.height = fgetc(f);
    printf("width = %u\n\n", image.width);
    printf("height = %u\n\n", image.height);
}

unsigned int get_width(FILE *f)
{
    unsigned int width;
    fseek(f, 18, 0);
    fread(&(width), 4, 1, f);
    return width;
}
unsigned int get_height(FILE *f)
{
    unsigned int height;
    fseek(f, 22, 0);
    fread(&(height), 4, 1, f);
    return height;
}

void do_RGB_matrix(unsigned int height, unsigned int width, RGB** matrix)
{
    matrix = (RGB **)calloc(height, sizeof(unsigned int *));
    for(unsigned int i = 0; i != height; i++)
    {
        matrix[i] = (RGB *)calloc(width, sizeof(unsigned int *));
    }
}
void do_BW_matrix(unsigned int height, unsigned int width, BW** m)
{
    while (!(height % 4)) height += 1;
    while (!(width  % 3))  width  += 1;
    
    m = (BW **)calloc(height, sizeof(unsigned int *));
    for(unsigned int i = 0; i < height; i++)
    {
        m[i] = (BW *)calloc(width, sizeof(unsigned int *));
    }
}

RGB** get_RGB_matrix(unsigned int height, unsigned int width, RGB** matrix,  FILE *f)
{
    fseek(f, 1078, 0);
    for (unsigned int i = 0; i != height; i++)
    {
        for (unsigned int j = 0; j != width; j++)
        {
            matrix[i][j].red = fgetc(f);
            if (matrix[i][j].red > 255) matrix[i][j].red = 666;
            matrix[i][j].green = fgetc(f);
            if (matrix[i][j].green > 255) matrix[i][j].green = 666;
            matrix[i][j].blue = fgetc(f);
            if (matrix[i][j].blue > 255) matrix[i][j].blue = 666;
        }
    }
    return matrix;
}
BW** get_BW_matrix(unsigned int height, unsigned int width, BW** m, RGB **matrix)
{
    for (unsigned int i = 0; i != height; i++)
    {
        for (unsigned int j = 0; j != width; j++)
        {
            m[i][j].darkness = (matrix[i][j].red + matrix[i][j].green + matrix[i][j].blue   ) / 3;
        }
    }
    return m;
}

void print_RGB_matrix(unsigned int height, unsigned int width, RGB **matrix)
{

    for (unsigned int i = 0; i != height; i++)
    {
        printf("[");
        for (unsigned int j = 0; j != width; j++)
        {
            printf(" %u.%u.%u ", matrix[i][j].red,  matrix[i][j].green, matrix[i][j].blue);
        }
        printf("]\n\n");
    }
}
void print_BW_matrix(unsigned int height, unsigned int width, BW** m)
{
    for (unsigned int i = 0; i != height; i++)
    {
        printf("[");
        for (unsigned int j = 0; j != width; j++)
        {
            printf(" %u ", m[i][j].darkness);
        }
        printf("]\n\n");
    }
}

