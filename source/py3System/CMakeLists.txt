set(TARGET py3System)
set(SRC module.cpp)

nanobind_add_module(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/source
)
target_link_libraries(${TARGET} PRIVATE
    System
)
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${TARGET} PROPERTIES LINK_FLAGS_RELEASE -s) 
endif()