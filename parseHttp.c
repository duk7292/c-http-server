
#include "parseHttp.h"


HTTP_METHOD get_http_method(char buffer[])
{
    char *saveptr;
    char *line = strtok_r(buffer, "\n", &saveptr);
    if(line)
    {
        printf("%s\n", line);
    }

    return GET;
}