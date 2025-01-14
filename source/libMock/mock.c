#include <assert.h>
#include <string.h>

#include "mock.h"

system_connect_info connect_info;
system_disconnect_info disconnect_info;
resource_open_info open_info;
resource_close_info close_info;
resource_lock_info lock_info;
resource_unlock_info unlock_info;
resource_process_info process_info;

void init_mocks() {
  memset(&connect_info, 0, sizeof(connect_info));
  memset(&disconnect_info, 0, sizeof(disconnect_info));
  memset(&open_info, 0, sizeof(open_info));
  memset(&close_info, 0, sizeof(close_info));
  memset(&lock_info, 0, sizeof(lock_info));
  memset(&unlock_info, 0, sizeof(unlock_info));
  memset(&process_info, 0, sizeof(process_info));
}

system_result system_connect(const char* user, const char* password, int* connection_id) {
  strcpy(connect_info.user, user);
  strcpy(connect_info.password, password);
  connect_info.called++;
  *connection_id = connect_info.connection_id;

  return connect_info.result;
}

system_result system_disconnect(int connection_id) {
  disconnect_info.connection_id = connection_id;
  disconnect_info.called++;

  return disconnect_info.result;
}

system_result resource_open(int connection_id, const char* resource, int* resource_id) {
  open_info.connection_id = connection_id;
  strcpy(open_info.resource, resource);
  *resource_id = open_info.resource_id;
  open_info.called++;

  return open_info.result;
}

system_result resource_close(int connection_id, int resource_id) {
  close_info.connection_id = connection_id;
  close_info.resource_id = resource_id;
  close_info.called++;

  return close_info.result;
}

system_result resource_lock(int connection_id, int resource_id) {
  lock_info.connection_id = connection_id;
  lock_info.resource_id = resource_id;
  lock_info.called++;

  return lock_info.result;
}

system_result resource_unlock(int connection_id, int resource_id) {
  unlock_info.connection_id = connection_id;
  unlock_info.resource_id = resource_id;
  unlock_info.called++;

  return unlock_info.result;
}

system_result resource_process(int connection_id, int resource_id) {
  process_info.connection_id = connection_id;
  process_info.resource_id = resource_id;
  process_info.called++;

  return process_info.result;
}
