#include <stdio.h>
#include <stdlib.h>
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
    if (!f)
    {
        printf("Error: File not open\n");
        return 5;
    }

    image.type = file_type_check(f);
    if (image.type)
    {
        fclose(f);////////////////////////////////////
        main();
    }
    
    fclose(f);////////////////////////////////////////////

    RGB** matrix;
    do_RGB_matrix(image.height, image.width, matrix);               //error
    
    f = fopen(way, "rb");//////////////////////////
    if (!f)
    {
        printf("Error: File not open\n");
        return -1;
    }
    //else printf("OK");
    get_RGB_matrix(image.height, image.width, matrix, f);        //error
    
    print_RGB_matrix(image.height, image.width, matrix);        //error
    printf("\nOK\n");
    
    
    fclose(f);////////////////////////////////////////////

    BW** m;
    do_BW_matrix(image.height, image.width, *m);                  //error
    get_BW_matrix(image.height, image.width, m, matrix);      //error
    
    free (matrix);
            
    print_BW_matrix(image.height, image.width, m);              //error
    
//
    
    free (m);
    return 0;
}
