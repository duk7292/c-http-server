#include "generateHttp.h"

char *get_response_buffer(hash_map *httpParse)
{
    char * response = NULL;	

    char *httpMethod = hm_get(httpParse, "http_method");
    if (!httpMethod)
    {
        response = strdup("HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 15\r\n"
            "Connection: close\r\n"
            "\r\n"
            "Invalid request\n");
        return response;
    }
    if (strcmp(httpMethod, "GET") == 0)
    {
        char* filepath = strdup("Files/");
        filepath = str_append(filepath,hm_get(httpParse,"endpoint"));
        FILE *fp = fopen(filepath,"rb");
        if(fp)
        {
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
            response = strdup("HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 15\r\n"
            "Connection: close\r\n"
            "\r\n"
            "File not found\n");
        }
        free(filepath);                  		
    }
    else
    {
        response = strdup("HTTP/1.1 405 Method Not Allowed\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 15\r\n"
            "Connection: close\r\n"
            "\r\n"
            "only GET allowed\n");
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
    
    
    response = str_append(response,"\r\nContent-Length: ");
    response = str_append(response, contentLength);
    
    //header end
    response = str_append(response,"\r\n\r\n");

    //body 
      
    response = str_append(response,body);

    return response;
}














