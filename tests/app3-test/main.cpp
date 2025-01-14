#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <libWrapper/wrapper.hpp>
#include <libWapp/wapp.hpp>

using testing::_;
using testing::DoAll;
using testing::Eq;
using testing::Ref;
using testing::Return;
using testing::SetArgPointee;
using testing::StrEq;
using testing::StrictMock;
using testing::Test;

class WrapperMock : public Wrapper {
 public:
  WrapperMock() = default;
  virtual ~WrapperMock() = default;

  MOCK_METHOD(system_result, system_connect, (const char*, const char*, int*),
              (override));
  MOCK_METHOD(system_result, system_disconnect, (int), (override));
  MOCK_METHOD(system_result, resource_open, (int, const char*, int*), (override));
  MOCK_METHOD(system_result, resource_close, (int, int), (override));
  MOCK_METHOD(system_result, resource_lock, (int, int), (override));
  MOCK_METHOD(system_result, resource_unlock, (int, int), (override));
  MOCK_METHOD(system_result, resource_process, (int, int), (override));
};

class AppTests : public Test {
 protected:
  const char* user{"admin"};
  const char* password{"Admin123"};
  const char* resource{"roles"};
  int connection_id;
  int resource_id;
};

TEST_F(AppTests, ConnectError) {
  StrictMock<WrapperMock> mock{};
  EXPECT_CALL(mock, system_connect(StrEq(user), StrEq(password), Eq(&connection_id)))
      .Times(1)
      .WillOnce(Return(ko));

  EXPECT_CALL(mock, system_disconnect(_)).Times(0);
  EXPECT_CALL(mock, resource_open(_, _, _)).Times(0);
  EXPECT_CALL(mock, resource_close(_, _)).Times(0);
  EXPECT_CALL(mock, resource_lock(_, _)).Times(0);
  EXPECT_CALL(mock, resource_unlock(_, _)).Times(0);
  EXPECT_CALL(mock, resource_process(_, _)).Times(0);

  auto result = app(&mock, user, password, resource, &connection_id, &resource_id);
  EXPECT_EQ(ko, result);
}

TEST_F(AppTests, OpenError) {
  StrictMock<WrapperMock> mock{};
  EXPECT_CALL(mock, system_connect(StrEq(user), StrEq(password), Eq(&connection_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(101), Return(ok)));

  EXPECT_CALL(mock, resource_open(Eq(101), StrEq(resource), Eq(&resource_id)))
      .Times(1)
      .WillOnce(Return(ko));

  EXPECT_CALL(mock, system_disconnect(Eq(101))).Times(1);

  EXPECT_CALL(mock, resource_close(_, _)).Times(0);
  EXPECT_CALL(mock, resource_lock(_, _)).Times(0);
  EXPECT_CALL(mock, resource_unlock(_, _)).Times(0);
  EXPECT_CALL(mock, resource_process(_, _)).Times(0);

  auto result = app(&mock, user, password, resource, &connection_id, &resource_id);
  EXPECT_EQ(ko, result);
  EXPECT_EQ(101, connection_id);
}

TEST_F(AppTests, LockError) {
  StrictMock<WrapperMock> mock{};
  EXPECT_CALL(mock, system_connect(StrEq(user), StrEq(password), Eq(&connection_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(101), Return(ok)));

  EXPECT_CALL(mock, resource_open(Eq(101), StrEq(resource), Eq(&resource_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(500), Return(ok)));

  EXPECT_CALL(mock, resource_lock(Eq(101), Eq(500))).Times(1).WillOnce(Return(ko));

  EXPECT_CALL(mock, resource_close(Eq(101), Eq(500))).Times(1);
  EXPECT_CALL(mock, system_disconnect(Eq(101))).Times(1);

  EXPECT_CALL(mock, resource_unlock(_, _)).Times(0);
  EXPECT_CALL(mock, resource_process(_, _)).Times(0);

  auto result = app(&mock, user, password, resource, &connection_id, &resource_id);
  EXPECT_EQ(ko, result);
  EXPECT_EQ(101, connection_id);
  EXPECT_EQ(500, resource_id);
}

TEST_F(AppTests, ProcessError) {
  StrictMock<WrapperMock> mock{};
  EXPECT_CALL(mock, system_connect(StrEq(user), StrEq(password), Eq(&connection_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(101), Return(ok)));

  EXPECT_CALL(mock, resource_open(Eq(101), StrEq(resource), Eq(&resource_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(500), Return(ok)));

  EXPECT_CALL(mock, resource_lock(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, resource_process(Eq(101), Eq(500))).Times(1).WillOnce(Return(ko));

  EXPECT_CALL(mock, resource_unlock(Eq(101), Eq(500))).Times(1);
  EXPECT_CALL(mock, resource_close(Eq(101), Eq(500))).Times(1);
  EXPECT_CALL(mock, system_disconnect(Eq(101))).Times(1);

  auto result = app(&mock, user, password, resource, &connection_id, &resource_id);
  EXPECT_EQ(ko, result);
  EXPECT_EQ(101, connection_id);
  EXPECT_EQ(500, resource_id);
}

TEST_F(AppTests, UnlockError) {
  StrictMock<WrapperMock> mock{};
  EXPECT_CALL(mock, system_connect(StrEq(user), StrEq(password), Eq(&connection_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(101), Return(ok)));

  EXPECT_CALL(mock, resource_open(Eq(101), StrEq(resource), Eq(&resource_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(500), Return(ok)));

  EXPECT_CALL(mock, resource_lock(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, resource_process(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, resource_unlock(Eq(101), Eq(500))).Times(1).WillOnce(Return(ko));

  EXPECT_CALL(mock, resource_close(Eq(101), Eq(500))).Times(1);
  EXPECT_CALL(mock, system_disconnect(Eq(101))).Times(1);

  auto result = app(&mock, user, password, resource, &connection_id, &resource_id);
  EXPECT_EQ(ko, result);
  EXPECT_EQ(101, connection_id);
  EXPECT_EQ(500, resource_id);
}

TEST_F(AppTests, CloseError) {
  StrictMock<WrapperMock> mock{};
  EXPECT_CALL(mock, system_connect(StrEq(user), StrEq(password), Eq(&connection_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(101), Return(ok)));

  EXPECT_CALL(mock, resource_open(Eq(101), StrEq(resource), Eq(&resource_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(500), Return(ok)));

  EXPECT_CALL(mock, resource_lock(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, resource_process(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, resource_unlock(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, resource_close(Eq(101), Eq(500))).Times(1).WillOnce(Return(ko));

  EXPECT_CALL(mock, system_disconnect(Eq(101))).Times(1);

  auto result = app(&mock, user, password, resource, &connection_id, &resource_id);
  EXPECT_EQ(ko, result);
  EXPECT_EQ(101, connection_id);
  EXPECT_EQ(500, resource_id);
}

TEST_F(AppTests, DisconnectSuccess) {
  StrictMock<WrapperMock> mock{};
  EXPECT_CALL(mock, system_connect(StrEq(user), StrEq(password), Eq(&connection_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(101), Return(ok)));

  EXPECT_CALL(mock, resource_open(Eq(101), StrEq(resource), Eq(&resource_id)))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(500), Return(ok)));

  EXPECT_CALL(mock, resource_lock(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, resource_process(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, resource_unlock(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, resource_close(Eq(101), Eq(500))).Times(1).WillOnce(Return(ok));

  EXPECT_CALL(mock, system_disconnect(Eq(101))).Times(1).WillOnce(Return(ok));

  auto result = app(&mock, user, password, resource, &connection_id, &resource_id);
  EXPECT_EQ(ok, result);
  EXPECT_EQ(101, connection_id);
  EXPECT_EQ(500, resource_id);
}