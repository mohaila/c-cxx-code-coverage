#pragma once

#include "wrapper.hpp"

class WrapperImpl : public Wrapper {
 public:
  WrapperImpl() = default;
  virtual ~WrapperImpl() = default;

  virtual system_result system_connect(const char* user, const char* password,
                                       int* connection_id) override;
  virtual system_result system_disconnect(int connection_id) override;

  virtual system_result resource_open(int connection_id, const char* resource,
                                      int* resource_id) override;
  virtual system_result resource_close(int connection_id, int resource_id) override;
  virtual system_result resource_lock(int connection_id, int resource_id) override;
  virtual system_result resource_unlock(int connection_id, int resource_id) override;
  virtual system_result resource_process(int connection_id, int resource_id) override;
};