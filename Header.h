#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include "structs.h"

int read_number(int, int);
char* smart_str();
char* request_way();
unsigned int file_type_check(FILE*);

//void get_size_of_matrix(BitMap, FILE*);
unsigned int get_width(FILE *f);
unsigned int get_height(FILE *f);

void do_RGB_matrix(unsigned int, unsigned int, RGB**);
void do_BW_matrix(unsigned int, unsigned int, BW**);

RGB** get_RGB_matrix(unsigned int, unsigned int, RGB**, FILE *);
BW** get_BW_matrix(unsigned int, unsigned int, BW**, RGB**);

void print_RGB_matrix(unsigned int, unsigned int, RGB**);
void print_BW_matrix(unsigned int, unsigned int, BW**);

#endif // HEADER_H
