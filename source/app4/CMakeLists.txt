set(TARGET app3)
set(SRC main.cpp)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_SOURCE_DIR}/source
)
target_link_libraries(${TARGET} PRIVATE
    Wapp
    Wrapper
    System
)
if(ENABLE_COVERAGE)
    target_compile_options(${TARGET} PRIVATE -O0 -coverage -fno-exceptions -fno-inline)
    target_link_options(${TARGET} PRIVATE -coverage)
elseif(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${TARGET} PROPERTIES LINK_FLAGS_RELEASE -s) 
endif()