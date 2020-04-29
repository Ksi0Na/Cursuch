#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include "structs.h"

int read_number(int, int);
char* request_way();
unsigned int file_type_check(FILE*);

void get_width(BitMap, FILE*);
void get_height(BitMap, FILE*);

void do_RGB_matrix(unsigned int, unsigned int, RGB**);
void do_BW_matrix(unsigned int, unsigned int, BW**);

void get_RGB_matrix(unsigned int, unsigned int, RGB**, FILE *);
void get_BW_matrix(unsigned int, unsigned int, BW**, RGB**);

void print_RGB_matrix(unsigned int, unsigned int, RGB**);
void print_BW_matrix(unsigned int, unsigned int, BW**);

#endif // HEADER_H
