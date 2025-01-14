#pragma once

#include <libSystem/system.h>

class Wrapper {
 public:
  Wrapper() = default;
  virtual ~Wrapper() = default;

  virtual system_result system_connect(const char* user, const char* password,
                                       int* connection_id) = 0;
  virtual system_result system_disconnect(int connection_id) = 0;

  virtual system_result resource_open(int connection_id, const char* resource,
                                      int* resource_id) = 0;
  virtual system_result resource_close(int connection_id, int resource_id) = 0;
  virtual system_result resource_lock(int connection_id, int resource_id) = 0;
  virtual system_result resource_unlock(int connection_id, int resource_id) = 0;
  virtual system_result resource_process(int connection_id, int resource_id) = 0;
};