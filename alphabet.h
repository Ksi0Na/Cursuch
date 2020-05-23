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

void get_alphabet();

#endif // ALPHABET_H
