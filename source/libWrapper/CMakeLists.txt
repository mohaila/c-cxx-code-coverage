set(TARGET Wrapper)
set(SRC wrapper.hpp wrapper_impl.hpp wrapper_impl.cpp)

add_library(${TARGET} STATIC ${SRC})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_SOURCE_DIR}/source
)