#include "generateHttp.h"

int is_regular_file(const char *path)
{
    //check if its a regular file and not a folder or anything else

    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
} 

int is_file_in_folder(char* filePath, char* folderPath)
{
    //check if a file is within a certian folder
    int folderPathLen = strlen(folderPath);
    int filePathLen = strlen(filePath);

    if(filePathLen < folderPathLen)
    {
        return 0;
    }

    for(int i = 0 ; i < folderPathLen ; i++)
    {
        if(folderPath[i] != filePath[i])
        {
            return 0;
        }
    }
    return 1;
}



char* validate_endpoint(char *endpoint)
{
    //if valid returns usable file path, otherwise NULL
    char* rawFilePath = strdup("public");
    rawFilePath = str_append(rawFilePath,endpoint);
    if(!rawFilePath)
    {
        free(rawFilePath); 
        return NULL;
    }
    char* filePath = realpath(rawFilePath, NULL);
    
    free(rawFilePath); 

    if(!filePath)
    {
        return NULL;
    }

    // *** check if file is in public folder *** 
    char* folderPath = strdup(realpath("public",NULL));
    bool is_path_allowed = is_file_in_folder(filePath,folderPath);
    free(folderPath);

    if(!is_path_allowed)
    {
        free(filePath);
        return NULL;
    }


    return filePath;
}

file_data get_file_data(char* file_path)
{
    // get the size and content of a file
    // returns empty struct if anything fails

    file_data fileData = {NULL,NULL,0};
    FILE *fp = fopen(file_path,"rb");
    
    if(!fp || !is_regular_file(file_path))
    {
        return fileData;
    }
    
    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char * fileBuffer = malloc(size +1);
    if (!fileBuffer) 
    {
        fclose(fp);
        return fileData;
    }

    size_t readSize = fread(fileBuffer,1,size,fp);
    fclose(fp);
    if(size != (long)readSize)
    {
        free(fileBuffer);
        return fileData;
    }
   

    fileData.fileBuffer = fileBuffer;
    fileData.size = size;
    fileData.content_type = get_content_type(file_path);

    return fileData;

}

char* compose_response_header(const char* content_type, long content_length)
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

    return response;
}

response_data get_response_buffer(hash_map *httpParse)
{
    response_data response = {NULL,NULL,0};	

    // *** Check for invalid requests *** 
    // Could be put into a separate function for clearer separation, but this works fine too.

    char *httpMethod = hm_get(httpParse, "http_method");
    if (!httpMethod)
    {
        return get_invalid_request_error_message();
    }
    if(!strcmp(httpMethod, "GET") == 0)
    {
        return get_method_not_allowed_error_message();
    }

    // **** check if endpoint is valid ****
    char* filePath = validate_endpoint(hm_get(httpParse,"endpoint"));

    if(!filePath)
    {
        return get_file_not_found_error_message(); 
    }
   
    file_data fileData = get_file_data(filePath);
    free(filePath);

    if(!fileData.fileBuffer)
    {
        return get_file_not_found_error_message();     
    }

    response.header = compose_response_header(fileData.content_type, fileData.size); 
    response.body = fileData.fileBuffer;
    response.body_size = fileData.size;  
    
    return response;
}














