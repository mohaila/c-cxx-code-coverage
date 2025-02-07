#include <libSystem/system.h>
#include <libMock/mock.h>
#include <libCWapp/app.h>
#include <libCWrapper/wrapper.h>

#include <gtest/gtest.h>

CWrapper* init_wrapper() {
  CWrapper* wrapper = (CWrapper*)malloc(sizeof(CWrapper));
  wrapper->system_connect = system_connect;
  wrapper->system_disconnect = system_disconnect;
  wrapper->resource_open = resource_open;
  wrapper->resource_close = resource_close;
  wrapper->resource_lock = resource_lock;
  wrapper->resource_unlock = resource_unlock;
  wrapper->resource_process = resource_process;

  return wrapper;
}

TEST(App2, ConnectError) {
  auto user = "admin";
  auto password = "Admin123";
  auto resource = "roles";
  int connection_id;
  int resource_id;

  init_mocks();

  CWrapper* wrapper = init_wrapper();

  connect_info.connection_id = 1;
  connect_info.result = ko;

  auto result = app(wrapper, user, password, resource, &connection_id, &resource_id);

  ASSERT_EQ(result, ko);
  ASSERT_STREQ(user, connect_info.user);
  ASSERT_STREQ(password, connect_info.password);
  ASSERT_EQ(connection_id, connect_info.connection_id);
  ASSERT_EQ(1, connect_info.called);
  ASSERT_EQ(0, disconnect_info.called);
  ASSERT_EQ(0, open_info.called);
  ASSERT_EQ(0, close_info.called);
  ASSERT_EQ(0, lock_info.called);
  ASSERT_EQ(0, unlock_info.called);
  ASSERT_EQ(0, process_info.called);

  free(wrapper);
}

TEST(App2, OpenError) {
  auto user = "admin";
  auto password = "Admin123";
  auto resource = "roles";
  int connection_id;
  int resource_id;

  init_mocks();

  CWrapper* wrapper = init_wrapper();

  connect_info.connection_id = 1;
  connect_info.result = ok;

  open_info.result = ko;

  auto result = app(wrapper, user, password, resource, &connection_id, &resource_id);

  ASSERT_EQ(result, ko);

  ASSERT_STREQ(user, connect_info.user);
  ASSERT_STREQ(password, connect_info.password);
  ASSERT_EQ(connection_id, connect_info.connection_id);
  ASSERT_EQ(1, connect_info.called);

  ASSERT_EQ(1, disconnect_info.called);
  ASSERT_EQ(1, disconnect_info.connection_id);

  ASSERT_EQ(1, open_info.called);
  ASSERT_EQ(1, open_info.connection_id);
  ASSERT_STREQ(resource, open_info.resource);

  ASSERT_EQ(0, close_info.called);
  ASSERT_EQ(0, lock_info.called);
  ASSERT_EQ(0, unlock_info.called);
  ASSERT_EQ(0, process_info.called);

  free(wrapper);
}