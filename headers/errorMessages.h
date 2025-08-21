#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

#include <string.h>
#include <stdlib.h>
#include "types.h"

response_data get_file_not_found_error_message();

response_data get_invalid_request_error_message();

response_data get_method_not_allowed_error_message();

#endif
