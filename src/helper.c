#include "../headers/helper.h"

char *str_append(char *strA, const char *strB)
{
    strA = realloc(strA, (strlen(strA) + strlen(strB) +1 ) * sizeof(char));

    memcpy(strA + strlen(strA), strB, strlen(strB) + 1);
    
    return strA;
}
