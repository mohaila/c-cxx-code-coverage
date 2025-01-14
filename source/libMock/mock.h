#pragma once

#include <libSystem/system.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char user[128];
  char password[128];
  int connection_id;
  int called;
  system_result result;
} system_connect_info;

typedef struct {
  int connection_id;
  system_result result;
  int called;
} system_disconnect_info;

typedef struct {
  int connection_id;
  char resource[128];
  int resource_id;
  int called;
  system_result result;
} resource_open_info;

typedef struct {
  int connection_id;
  int resource_id;
  int called;
  system_result result;
} resource_close_info;

typedef struct {
  int connection_id;
  int resource_id;
  int called;
  system_result result;
} resource_lock_info;

typedef struct {
  int connection_id;
  int resource_id;
  int called;
  system_result result;
} resource_unlock_info;

typedef struct {
  int connection_id;
  int resource_id;
  int called;
  system_result result;
} resource_process_info;

extern system_connect_info connect_info;
extern system_disconnect_info disconnect_info;
extern resource_open_info open_info;
extern resource_close_info close_info;
extern resource_lock_info lock_info;
extern resource_unlock_info unlock_info;
extern resource_process_info process_info;

void init_mocks();

#ifdef __cplusplus
}
#endif