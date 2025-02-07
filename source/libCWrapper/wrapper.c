#include <stdlib.h>

#include "wrapper.h"

static system_result wrap_system_connect(const char* user, const char* password,
                                         int* connection_id) {
  return system_connect(user, password, connection_id);
}

static system_result wrap_system_disconnect(int connection_id) {
  return system_disconnect(connection_id);
}

static system_result wrap_resource_open(int connection_id, const char* resource,
                                        int* resource_id) {
  return resource_open(connection_id, resource, resource_id);
}

static system_result wrap_resource_close(int connection_id, int resource_id) {
  return resource_close(connection_id, resource_id);
}

static system_result wrap_resource_lock(int connection_id, int resource_id) {
  return resource_lock(connection_id, resource_id);
}

static system_result wrap_resource_unlock(int connection_id, int resource_id) {
  return resource_unlock(connection_id, resource_id);
}

static system_result wrap_resource_process(int connection_id, int resource_id) {
  return resource_process(connection_id, resource_id);
}

CWrapper* init_wrapper() {
  CWrapper* wrapper = (CWrapper*)malloc(sizeof(CWrapper));
  wrapper->system_connect = wrap_system_connect;
  wrapper->system_disconnect = wrap_system_disconnect;
  wrapper->resource_open = wrap_resource_open;
  wrapper->resource_close = wrap_resource_close;
  wrapper->resource_lock = wrap_resource_lock;
  wrapper->resource_unlock = wrap_resource_unlock;
  wrapper->resource_process = wrap_resource_process;

  return wrapper;
}
