#include <libSystem/system.h>
#include <nanobind/nanobind.h>

int connect_wrapper(const char *user, const char *password) {
  int connection;
  auto result = system_connect(user, password, &connection);
  if (result == ok) {
    return connection;
  }
  return fail;
}

int open_wrapper(int connection, const char *resource) {
  int id;
  auto result = resource_open(connection, resource, &id);
  if (result == ok) {
    return id;
  }
  return fail;
}

NB_MODULE(py3System, m) {
  m.doc() = "System Python binding";

  m.def("system_connect", connect_wrapper, "System connect");
  m.def("system_disconnect", system_disconnect, "System disconnect");
  m.def("resource_open", open_wrapper, "Open System resource");
  m.def("resource_close", resource_close, "Close System resource");
  m.def("resource_lock", resource_lock, "Lock System resource");
  m.def("resource_unlock", resource_unlock, "Unlock System resource");
  m.def("resource_process", resource_process, "Process System resource");

  nanobind::enum_<system_result>(m, "result", "System call result")
      .value("fail", system_result::fail, "System call failure")
      .value("ok", system_result::ok, "System call success")
      .value("ko", system_result::ko, "System call error");
}