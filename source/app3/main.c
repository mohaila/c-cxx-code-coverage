#include <stdlib.h>
#include <libCWrapper/wrapper.h>
#include <libCWapp/app.h>

int main(int argc, const char** argv) {
  const char* user = "admin";
  const char* password = "Admin123";
  const char* resource = "users";

  int connection_id;
  int resource_id;

  CWrapper* wrapper = init_wrapper();

  system_result result =
      app(wrapper, user, password, resource, &connection_id, &resource_id);

  free(wrapper);

  return result;
}