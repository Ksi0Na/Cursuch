#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include "structs.h"

int check_open_file(char*, FILE*);

int read_number(int, int);
char* smart_str();
char* request_way();
unsigned int file_type_check(FILE*);

//void get_size_of_matrix(BitMap, FILE*);
unsigned int get_width(FILE *f);
unsigned int get_height(FILE *f);

void do_RGB_matrix(unsigned int, unsigned int, RGB**);
void do_BW_matrix(unsigned int, unsigned int, BW**);

void get_RGB_matrix(unsigned int, unsigned int, RGB**, FILE *);
void get_BW_matrix(unsigned int, unsigned int, BW**, RGB**);
void get_BW_matrix_3x4(unsigned int, unsigned int, unsigned int, BW***, BW**);

void do_white(unsigned int, unsigned int, BW**);

void print_RGB_matrix(unsigned int, unsigned int, RGB**);
void print_BW_matrix(unsigned int, unsigned int, BW**);
void print_RGB_matrix_in_file(unsigned int, unsigned int, FILE*);
void print_BW_matrix_3x4(unsigned int, unsigned int, unsigned int, BW***);


#endif // HEADER_H
