#pragma once

#include <libSystem/system.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  system_result (*system_connect)(const char* user, const char* password,
                                  int* connection_id);
  system_result (*system_disconnect)(int connection_id);

  system_result (*resource_open)(int connection_id, const char* resource,
                                 int* resource_id);
  system_result (*resource_close)(int connection_id, int resource_id);
  system_result (*resource_lock)(int connection_id, int resource_id);
  system_result (*resource_unlock)(int connection_id, int resource_id);
  system_result (*resource_process)(int connection_id, int resource_id);
} CWrapper;

CWrapper* init_wrapper();

#ifdef __cplusplus
}
#endif