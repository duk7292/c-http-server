#ifndef PARSE_HTTP_H
#define PARSE_HTTP_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "hashMap.h"



hash_map *parse_http(char buffer[]);

int parse_request_line(hash_map *hm, char firstLine[]);

int parse_header(hash_map *hm, char **rawHeader, int headerSize);

#endif
