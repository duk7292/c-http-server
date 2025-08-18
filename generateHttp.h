#ifndef GENERATE_HTTP_H
#define GENERATE_HTTP_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "helper.h"
#include "hashMap.h"
#include "errorMessages.h"
#include "types.h"
#include "contentTypeConversion.h"

int is_regular_file(const char* path);

int is_file_in_folder(char* filePath, char* folderPath);

char *validate_endpoint(char* endpoint);

file_data get_file_data(char* file_path);

char* compose_response_header(const char* content_type,long content_length);

response_data get_response_buffer( hash_map *httpParse);




#endif
