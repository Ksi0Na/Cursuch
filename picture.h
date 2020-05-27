#ifndef PICTURE_H
#define PICTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _RGB
{
    int width;
    int height;
    
    int **red;
    int **green;
    int **blue;

} RGB;

typedef struct _BW
{
    int w;
    int h;
    
    int **m;

} BW;

typedef struct _COEF
{
    int w;
    int h;
    unsigned c;
    
    double ***m;

} COEF;


int check_open_file(char*, FILE*);

int read_number(int, int);
char* smart_str();
char* request_way();
int file_type_check(FILE*);
//////////////////////////////////////
int get_width(FILE*);
int get_height(FILE*);

RGB* memory_RGB(int, int);
void get_RGB_matrix(int, int, RGB*, FILE*);
void delete_RGB(RGB*);
//////////////////////////////////////
int get_new_width(int, int);
int get_new_height(int, int);
void do_white(BW*);

BW* memory_BW(int, int);
void get_BW_matrix(int, int, RGB*, BW*);
int get_BW_m(BW*, int, int);
void delete_BW(BW*);
//////////////////////////////////////
COEF* memory_COEF(unsigned int, int, int);
void get_COEF_matrix(unsigned int, int, int, BW*, COEF*);
void get_coef(COEF*);
void set_COEF_m(COEF*, unsigned, int, int, int);
void delete_COEF(COEF*);

COEF* work_with_file_matrix();

#endif // PICTURE_H
