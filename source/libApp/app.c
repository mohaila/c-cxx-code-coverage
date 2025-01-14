#include "app.h"

system_result app(const char* user, const char* password, const char* resource, int* connection_id,
                  int* resource_id) {
  system_result result = system_connect(user, password, connection_id);
  if (result != ok) {
    return result;
  }

  result = resource_open(*connection_id, resource, resource_id);
  if (result != ok) {
    system_disconnect(*connection_id);
    return result;
  }

  result = resource_lock(*connection_id, *resource_id);
  if (result != ok) {
    resource_close(*connection_id, *resource_id);
    system_disconnect(*connection_id);
    return result;
  }

  result = resource_process(*connection_id, *resource_id);
  if (result != ok) {
    resource_unlock(*connection_id, *resource_id);
    resource_close(*connection_id, *resource_id);
    system_disconnect(*connection_id);
    return result;
  }

  result = resource_unlock(*connection_id, *resource_id);
  if (result != ok) {
    resource_close(*connection_id, *resource_id);
    system_disconnect(*connection_id);
    return result;
  }

  result = resource_close(*connection_id, *resource_id);
  if (result != ok) {
    system_disconnect(*connection_id);
    return result;
  }

  return system_disconnect(*connection_id);
}