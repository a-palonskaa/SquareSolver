#include "get_data.h"

int GetData(struct coeff *pointer) {

    int flag = 0;

    do {
        printf("Enter a, b, c \n");

        flag = scanf("%lg %lg %lg", &(pointer->a), &(pointer->b) , &(pointer->c));

        if(flag == EOF)
        {
            return INPUT_ERROR;
        }

        if (BuferClean() == 0) return INPUT_ERROR;
    } while(flag != 3);
    return 1;
}
