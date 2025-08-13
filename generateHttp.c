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
            FILE *fp = fopen("Files/index.html","rb");
            fseek(fp,0,SEEK_END);
            long size = ftell(fp);
            rewind(fp);

            char * fileBuffer = malloc(size +1);
            fread(fileBuffer,1,size,fp);
            fileBuffer[size] = '\0';
                        
            response = compose_response("text/html", size, fileBuffer); 

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
        return("HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: 15\r\n"
             "Connection: close\r\n"
             "\r\n"
             "Invalid request\n");
    }
    
    return response;
}


char* compose_response(char* content_type, long content_length,char* body)
{
    char* response = NULL;
    
    response = strdup("HTTP/1.1 200 OK\r\n"
            "Content-Type: ");
    // Type
    response = str_append(response,content_type);
    
    // Length
    char contentLength[12];
    sprintf(contentLength, "%ld", content_length);

            printf("debug start\n");
    response = str_append(response,"\r\nContent-Length: ");

            printf("debug end\n");
    response = str_append(response, contentLength);
    
    //header end
    response = str_append(response,"\r\n\r\n");

    //body 
    response = str_append(response,body);

    return response;
}














