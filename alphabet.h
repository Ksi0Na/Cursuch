#ifndef ALPHABET_H
#define ALPHABET_H

typedef struct _Alphabet
{
    char symbol;
    char matrix[20][13];

} Alphabet;

typedef struct _Alphabet_new
{
    char symbol;
    char matrix[260][1];

} Alphabet_new;


Alphabet_new get_alphabet_new(int new_M, int new_N, 
                                      Alphabet);

Alphabet_new* work_with_alphabet();

#endif // ALPHABET_H
