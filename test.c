#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "helper.c"

int main()
{
    while (1)
    {
        char *a = NULL;
        char *b = NULL;

        a = strdup("heysssssssss A");
        b = strdup("hessssssssy B");

        a = str_append(a, b);

        printf("%s\n", a);

        free(a);
        free(b);
        print_memory_usage();
    }

    return 0;
}