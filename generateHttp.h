#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "helper.h"
#include "hashMap.h"

#ifndef GENERATE_HTTP_H
#define GENERATE_HTTP_H

char* get_response_buffer( hash_map *httpParse);

char* compose_response(char* content_type,long content_length,char* body);

#endif
