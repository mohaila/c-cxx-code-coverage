#include <libSystem/system.h>
#include <libMock/mock.h>
#include <libApp/app.h>

#include <gtest/gtest.h>

TEST(App2, ConnectError) {
  auto user = "admin";
  auto password = "Admin123";
  auto resource = "roles";
  int connection_id;
  int resource_id;

  init_mocks();

  connect_info.connection_id = 1;
  connect_info.result = ko;

  auto result = app(user, password, resource, &connection_id, &resource_id);

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
}

TEST(App2, OpenError) {
  auto user = "admin";
  auto password = "Admin123";
  auto resource = "roles";
  int connection_id;
  int resource_id;

  init_mocks();

  connect_info.connection_id = 1;
  connect_info.result = ok;

  open_info.result = ko;

  auto result = app(user, password, resource, &connection_id, &resource_id);

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
}