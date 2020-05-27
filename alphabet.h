#ifndef ALPHABET_H
#define ALPHABET_H

typedef struct _Alphabet
{
    char symbol;
    char matrix[20][13];

} A;

typedef struct _AlphabetColumn
{
    char symbol;
    char **matrix;

} AC;


AC* get_alphabet_new(int new_M, int new_N, A);

AC* work_with_alphabet();

void delete_AC(AC*);

#endif // ALPHABET_H
