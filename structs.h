#ifndef STUCTS_H
#define STUCTS_H

typedef struct _BW
{
    unsigned int darkness;

} BW;

typedef struct _RGB
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;

} RGB;

typedef struct _BitMap
{
    unsigned int type;                      // 1-error
    unsigned int width;                     // ширина
    unsigned int height;                    // высота

} BitMap;

#endif // STUCTS_H
