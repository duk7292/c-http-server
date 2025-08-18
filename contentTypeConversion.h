#ifndef MIME_CONVERSION_H
#define MIME_CONVERSION_H

#include <string.h>

struct mime_entry 
{
    const char *ext;
    const char *type;
};

static const struct mime_entry mime_types[] = 
{
    { ".html", "text/html" },
    { ".jpg",  "image/jpeg" },
    { ".png",  "image/png" },
    { ".css",  "text/css" },
    { ".js",   "application/javascript" },
    { NULL,    "application/octet-stream" } 
};

const char* get_content_type(const char *filename) ;

#endif