#include "system.h"

#include <stdio.h>

system_result system_connect(const char* user, const char* password, int* connection_id) {
  printf("System connect - user: %s\n", user);

  *connection_id = 1;
  printf("System connect - connection id: %d\n", *connection_id);

  return ok;
}

system_result system_disconnect(int connection_id) {
  printf("System disconnect - connection id: %d\n", connection_id);

  return ok;
}

system_result resource_open(int connection_id, const char* resource, int* resource_id) {
  printf("Resource open - connection id: %d - resource: %s\n", connection_id, resource);

  *resource_id = 1;
  printf("Resource open - resource id: %d\n", *resource_id);

  return ok;
}

system_result resource_close(int connection_id, int resource_id) {
  printf("Resource close - connection id: %d - resource id: %d\n", connection_id, resource_id);

  return ok;
}

system_result resource_lock(int connection_id, int resource_id) {
  printf("Resource lock - connection id: %d - resource id: %d\n", connection_id, resource_id);

  return ok;
}

system_result resource_unlock(int connection_id, int resource_id) {
  printf("Resource unlock - connection id: %d - resource id: %d\n", connection_id, resource_id);

  return ok;
}

system_result resource_process(int connection_id, int resource_id) {
  printf("Resource process - connection id: %d - resource id: %d\n", connection_id, resource_id);

  return ok;
}