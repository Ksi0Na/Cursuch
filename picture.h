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

typedef struct _BW
{
    float darkness;

} BW;


int check_open_file(char*, FILE*);

int read_number(int, int);
char* smart_str();
char* request_way();
int file_type_check(FILE*);

int get_width(FILE *f);
int get_height(FILE *f);
void get_RGB_matrix(int, int, RGB**, FILE *f);

int get_new_width(int, int);
int get_new_height(int, int);
void do_white(int, int, BW**);
void get_BW_matrix(int, int, BW**, RGB **);

#endif // PICTURE_H
