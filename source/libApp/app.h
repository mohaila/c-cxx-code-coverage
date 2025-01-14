#pragma once

#include <libSystem/system.h>

#ifdef __cplusplus
extern "C" {
#endif

system_result app(const char* user, const char* password, const char* resource, int* connection_id,
                  int* resource_id);

#ifdef __cplusplus
}
#endif