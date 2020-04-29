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
char* request_way()
{
    char* way = (char*)malloc(sizeof(char));
    way[0] = '\0';
    printf("Enter the way to the file\n");
    char s = getchar();
    while (s != '\n')
    {
        way = (char*)realloc(way, sizeof(char) * (strlen(way) + 2));
        strncat(way, &s, 1);
        s = getchar();
    }

    int choise;
    printf("%s\n", way);
    printf("[0] continure\n");
    printf("[1] repeat the input\n");
    choise = read_number(0, 1);
    if (choise) { request_way(); }

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

void get_width(BitMap image, FILE *f)
{
    fseek(f, 18, 0);
    fread(&(image.width), 4, 1, f);
}
void get_height(BitMap image, FILE *f)
{
    fseek(f, 22, 0);
    fread(&(image.height), 4, 1, f);
}

void do_RGB_matrix(unsigned int height, unsigned int width, RGB**matrix)
{
    matrix = (RGB **)malloc(height*sizeof(unsigned int *));
    for(unsigned int i = 0; i < height; i++)
    {
        matrix[i] = (RGB *)malloc(width*sizeof(unsigned int *));
    }
}
void do_BW_matrix(unsigned int height, unsigned int width, BW** m)
{
    m = (BW **)malloc(height*sizeof(unsigned int *));
    for(unsigned int i = 0; i < height; i++)
    {
        m[i] = (BW *)malloc(width*sizeof(unsigned int *));
    }
}

void get_RGB_matrix(unsigned int height, unsigned int width, RGB** matrix,  FILE *f)
{
    fseek(f, 1078, 0);
    
    unsigned int i = 0;
    unsigned int j = 0;
    for (; i != height; i++)
    {
        for (; j != width; j++)
        {
            matrix[i][j].red = fgetc(f);
            matrix[i][j].green = fgetc(f);
            matrix[i][j].blue = fgetc(f);
        }
    }
}
void get_BW_matrix(unsigned int height, unsigned int width, BW** m, RGB **matrix)
{
    for (unsigned int i = 0; i != height; i++)
    {
        for (unsigned int j = 0; j != width; j++)
        {
            m[i][j] = (matrix[i][j].red + matrix[i][j].green + matrix[i][j].blue   ) / 3;
        }
    }
}

void print_RGB_matrix(unsigned int height, unsigned int width, RGB **matrix)
{
    unsigned int i = 0;
    unsigned int j = 0;
    for (; i != height; i++)
    {
        printf("[");
        for (; j != width; j++)
        {
            printf(" {%u}{%u}{%u} ", matrix[i][j].red,  matrix[i][j].green, matrix[i][j].blue);
        }
        printf("]\n");
    }
}
void print_BW_matrix(unsigned int height, unsigned int width, BW** m)
{
    unsigned int i = 0;
    unsigned int j = 0;
    for (; i != height; i++)
    {
        printf("[");
        for (; j != width; j++)
        {
            printf(" %u ", m[i][j].darkness);
        }
        printf("]\n");
    }
}
