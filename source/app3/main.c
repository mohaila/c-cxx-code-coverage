#include <libApp/app.h>

int main(int argc, const char** argv) {
  const char* user = "admin";
  const char* password = "Admin123";
  const char* resource = "users";

  int connection_id;
  int resource_id;

  return app(user, password, resource, &connection_id, &resource_id);
}