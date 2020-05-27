#ifndef ALPHABET_H
#define ALPHABET_H

typedef struct _Alphabet
{
    char symbol;
    int matrix[20][13];

} A;

typedef struct _AlphabetColumn
{
    char symbol;
    int **matrix;

} AC;


void get_AC(int new_M, int new_N, AC*);

AC* work_with_alphabet();

AC* get_memoty_AC();

void delete_AC(AC*);

#endif // ALPHABET_H
