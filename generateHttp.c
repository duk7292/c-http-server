#include "generateHttp.h"

char *get_response_buffer(hash_map *httpParse)
{
    char * response = NULL;	
    bool valid = true;
    char *httpMethod = hm_get(httpParse, "http_method");
    if (httpMethod)
    {
        if (strcmp(httpMethod, "GET") == 0)
        {

        	response = strdup("HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html\r\n"
                           "Content-Length: 200\r\n"
                           "Connection: close\r\n"
                           "\r\n");
            FILE *fp = fopen("Files/index.html","rb");
            fseek(fp,0,SEEK_END);
            long size = ftell(fp);
            rewind(fp);

            char * fileBuffer = malloc(size +1);
            fread(fileBuffer,1,size,fp);
            fileBuffer[size] = '\0';
            
            response = str_append(response,fileBuffer);

            free(fileBuffer);   
            fclose(fp);
                            		
        }
        else
        {
            valid = false;
        }
    }
    else
    {
        valid = false;
    }
    if (!valid)
    {
        response = strdup("HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html\r\n"
                           "Content-Length: 13\r\n"
                           "Connection: close\r\n"
                           "\r\n"
                           "Invalid request");
    }
    return response;
}
