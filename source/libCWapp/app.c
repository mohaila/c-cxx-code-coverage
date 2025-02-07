#include "app.h"

system_result app(CWrapper* wrapper, const char* user, const char* password,
                  const char* resource, int* connection_id, int* resource_id) {
  system_result result = wrapper->system_connect(user, password, connection_id);
  if (result != ok) {
    return result;
  }

  result = wrapper->resource_open(*connection_id, resource, resource_id);
  if (result != ok) {
    wrapper->system_disconnect(*connection_id);
    return result;
  }

  result = wrapper->resource_lock(*connection_id, *resource_id);
  if (result != ok) {
    wrapper->resource_close(*connection_id, *resource_id);
    wrapper->system_disconnect(*connection_id);
    return result;
  }

  result = wrapper->resource_process(*connection_id, *resource_id);
  if (result != ok) {
    wrapper->resource_unlock(*connection_id, *resource_id);
    wrapper->resource_close(*connection_id, *resource_id);
    wrapper->system_disconnect(*connection_id);
    return result;
  }

  result = wrapper->resource_unlock(*connection_id, *resource_id);
  if (result != ok) {
    wrapper->resource_close(*connection_id, *resource_id);
    wrapper->system_disconnect(*connection_id);
    return result;
  }

  result = wrapper->resource_close(*connection_id, *resource_id);
  if (result != ok) {
    wrapper->system_disconnect(*connection_id);
    return result;
  }

  return wrapper->system_disconnect(*connection_id);
}