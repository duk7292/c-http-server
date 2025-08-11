
#include "parseHttp.h"


hash_map* parse_http(char buffer[])
{
    hash_map* hashMap = hm_create(100);


    // split sections

    char* token = strtok(buffer, "\n");

    char* request_line = token;

    int capacity = 5;

    char** header = malloc(capacity*sizeof(char*));
    int headerSize = 0;
    token = strtok(NULL, "\n");

    while(token)
    {
        if (strcmp(token, "\r") == 0 || strcmp(token, "") == 0) 
        {
            break;
        }
        headerSize++;
        
        if(headerSize >= capacity)
        {
            capacity*=2;
            header = realloc (header,capacity *sizeof(char*));
        }
        header[headerSize-1] = token;
        token = strtok(NULL, "\n");
    }

    char* body = strtok(NULL, "");

    
    // add sections to hashmap
    parse_request_line(hashMap,request_line);

    parse_header(hashMap, header, headerSize);

    hm_put(hashMap,"body",body);
  

    free(header);
    
    return hashMap;
}

int parse_header(hash_map* hm, char** rawHeader, int headerSize)
{
    for(int i = 0; i< headerSize;i++)
    {
        char* start =  strtok(rawHeader[i], ": ");
        char* end =  strtok(NULL, "");

        hm_put(hm,start,end);
    }
    
}

int parse_request_line(hash_map* hm, char firstLine[])
{
    char* firstLineSplit = strtok(firstLine, " ");
    int count = 0;
    while(firstLineSplit)
    {
        switch (count)
        {
        case 0:
            hm_put(hm,"http_method",firstLineSplit);
            break;
        case 1:
            hm_put(hm,"endpoint",firstLineSplit);
            break;
        case 2:
            hm_put(hm,"http_version",firstLineSplit);
            break;

        }
        count++;
        firstLineSplit = strtok(NULL, " ");
    }
    return 0;
}