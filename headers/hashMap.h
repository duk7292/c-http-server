#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//simple Hashmap for strings

typedef struct 
{
    char ***identifiers;
    char ***values;
    int size;
    int *spaceMap;

} hash_map;

hash_map* hm_create(int size);
int hm_free(hash_map* hm);


char* hm_get(hash_map* hm,char* identifier);

int hm_put(hash_map* hm, char* identifier , char * value);

int string_to_hash(char* s , int size);
#endif

