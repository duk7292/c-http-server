#include "../headers/contentTypeConversion.h"


const char* get_content_type(const char *filename) 
{
    const char *dot = strrchr(filename, '.'); 

    if (!dot)
    {
         return "application/octet-stream"; 
    }
    
    for (int i = 0; mime_types[i].ext; i++) 
    {
        if (strcmp(dot, mime_types[i].ext) == 0) 
        {
            return mime_types[i].type;
        }
    }
    return "application/octet-stream";
}
