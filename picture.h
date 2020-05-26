#ifndef PICTURE_H
#define PICTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _RGB
{
    int red;
    int green;
    int blue;

} RGB;


int check_open_file(char*, FILE*);

int read_number(int, int);
char* smart_str();
char* request_way();
int file_type_check(FILE*, char*);

int get_width(FILE *f);
int get_height(FILE *f);
void get_RGB_matrix(int, int, RGB**, FILE *f);

int get_new_width(int, int);
int get_new_height(int, int);
void do_white(int, int, int**);
void get_BW_matrix(int, int, int**, RGB **);

RGB** do_RGB(FILE*);
void delete_RGB(RGB**, int);

int** do_BW_matrix(int, int, int, int, RGB**);
void delete_BW(int**, int);

double*** do_matrix_NxM(unsigned int, int, int, 
                                             int, int, int**);

#endif // PICTURE_H
