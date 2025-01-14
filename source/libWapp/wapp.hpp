#pragma once

#include <libSystem/system.h>
#include <libWrapper/wrapper.hpp>

system_result app(Wrapper* wrapper, const char* user, const char* password,
                  const char* resource, int* connection_id, int* resource_id);
