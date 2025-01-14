#include "wrapper_impl.hpp"

system_result WrapperImpl::system_connect(const char* user, const char* password,
                                          int* connection_id) {
  return ::system_connect(user, password, connection_id);
}

system_result WrapperImpl::system_disconnect(int connection_id) {
  return ::system_disconnect(connection_id);
}

system_result WrapperImpl::resource_open(int connection_id, const char* resource,
                                         int* resource_id) {
  return ::resource_open(connection_id, resource, resource_id);
}

system_result WrapperImpl::resource_close(int connection_id, int resource_id) {
  return ::resource_close(connection_id, resource_id);
}

system_result WrapperImpl::resource_lock(int connection_id, int resource_id) {
  return ::resource_lock(connection_id, resource_id);
}

system_result WrapperImpl::resource_unlock(int connection_id, int resource_id) {
  return ::resource_unlock(connection_id, resource_id);
}

system_result WrapperImpl::resource_process(int connection_id, int resource_id) {
  return ::resource_process(connection_id, resource_id);
}