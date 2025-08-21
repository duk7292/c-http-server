#include "../headers/errorMessages.h"


response_data get_file_not_found_error_message()
{
    response_data Data = {strdup("HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 15\r\n"
            "Connection: close\r\n"
            "\r\n"),strdup("File not found\n"),15};
    return Data;
}

response_data get_invalid_request_error_message()
{
    response_data Data = {strdup("HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 15\r\n"
            "Connection: close\r\n"
            "\r\n"),strdup("Invalid request\n"),15};
    return Data;
}

response_data get_method_not_allowed_error_message()
{
    response_data Data = {strdup("HTTP/1.1 405 Method Not Allowed\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 15\r\n"
            "Connection: close\r\n"
            "\r\n"),strdup("only GET allowed\n"),15};
    return Data;
}

