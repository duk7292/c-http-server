#ifndef TYPES_H
#define TYPES_H

typedef struct 
{
    char *fileBuffer;
    const char *content_type;
    long size;
    
} file_data;

typedef struct 
{
    char *header;
    char *body;
    long body_size;
    
} response_data;

#endif