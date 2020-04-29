#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structs.h"
#include "Header.h"

int main()
{
    char* way = request_way();

    BitMap image;
    FILE *f;

    f = fopen(way, "r");////////////////////////////////////
    if (!f) {
        printf("Error: File not open\n");
        main();
    }
    image.type = file_type_check(f);
    if (image.type) {
        fclose(f);//////////////////////////////////////////
        main();
    } else {
        image.width = get_width(f);
        image.height = get_height(f);
//        printf("width = %u\n\n", image.width);
//        printf("height = %u\n\n", image.height);
    }
    fclose(f);////////////////////////////////////////////

  
    RGB **matrix; 
    matrix = (RGB **)calloc(image.height, sizeof(unsigned int *));
    for(unsigned int i = 0; i < image.height; i++)
    {
        matrix[i] = (RGB *)calloc(image.width, sizeof(unsigned int *));
    }
    
    f = fopen(way, "rb");///////////////////////////////////
    if (!f)
    {
        printf("Error: File not open\n");
        return -1;
    }
    get_RGB_matrix(image.height, image.width, matrix, f);        //error
    print_RGB_matrix(image.height, image.width, matrix);        
    fclose(f);////////////////////////////////////////////

    BW** m;
    while (!(image.height % 4)) image.height += 1;
    while (!(image.width  % 3))  image.width  += 1;
    
    m = (BW **)calloc(image.height, sizeof(unsigned int *));
    for(unsigned int i = 0; i < image.height; i++)
    {
        m[i] = (BW *)calloc(image.width, sizeof(unsigned int *));
    }
    
    get_BW_matrix(image.height, image.width, m, matrix);      //error 
    print_BW_matrix(image.height, image.width, m);   
    free (matrix);
    
//
    
    free (m);
    
    
    return 0;
}
