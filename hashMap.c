#include "hashMap.h"

hash_map* hm_create(int size)
{
    /*create a hash_map of strings its empty at first*/
    hash_map *hm = malloc(sizeof(hash_map));

    hm->identifiers = malloc(size * sizeof(char**));
    hm->values  = malloc(size * sizeof(char**));

    hm->spaceMap = malloc(size * sizeof(int));

    for (int i = 0; i<size; i++)
    {
        
        hm->identifiers[i] = NULL;
        hm->values[i] = NULL;
        hm->spaceMap[i] = 0;
    }
    
    hm->size = size;

    return hm;
}

int hm_free(hash_map* hm)
{
    for (int i = 0; i < hm->size; i++)
    {
        for (int j = 0; j < hm->spaceMap[i] ; j++)
        {
            free(hm->identifiers[i][j]);
            free(hm->values[i][j]);
        }
        free(hm->identifiers[i]);
        free(hm->values[i]);

    }
    free(hm->spaceMap);
    free(hm->values);
    free(hm->identifiers);
    free(hm);
}


int hm_put(hash_map* hm, char* identifier , char * value)
{
    /*
    add new value
    return 0 - > success
    return 1 - > identifier already exists
    */
    int index = string_to_hash(identifier,hm->size);

    int spaceUsed = hm->spaceMap[index];

  
    //chek if identifier already is in hashmap
    for(int i = 0; i < spaceUsed; i++)
    {
        if (strcmp(hm->identifiers[index][i], identifier) == 0)
        {
            return 1;
        }
    }
    
    //increase space by one
    hm->identifiers[index] = realloc(hm->identifiers[index],(spaceUsed+1)* sizeof(char*));

    hm->values[index] = realloc(hm->values[index],(spaceUsed+1)* sizeof(char*));
 
    

    //add value
    hm->identifiers[index][spaceUsed] = strdup(identifier);
    hm->values[index][spaceUsed] = strdup(value);

  
    hm->spaceMap[index]++;
    return 0;
}

char* hm_get(hash_map* hm,char* identifier)
{
    /*
    get value by identifier
    */

    int index = string_to_hash(identifier,hm->size);

    int spaceUsed = hm->spaceMap[index]; 
    for(int i = 0; i < spaceUsed; i++)
    {
        if (strcmp(hm->identifiers[index][i], identifier) == 0)
        {

            return hm->values[index][i];
        }
    }
    return NULL;
}

int string_to_hash(char *s, int size) 
{
    if (size <= 0)
    {
        return 0;
    }

    unsigned long long h = 0;  

    for (size_t i = 0; s[i]; ++i) 
    {
        h = (h * 53u + (unsigned char)s[i]) % (unsigned long long)size;
    }
    
    return (int)h;                       
}