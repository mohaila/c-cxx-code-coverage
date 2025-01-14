set(TARGET App)
set(SRC app.h app.c)

add_library(${TARGET} STATIC ${SRC})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_SOURCE_DIR}/source
)

if(ENABLE_COVERAGE)
    target_compile_options(${TARGET} PRIVATE -O0 -coverage -fno-exceptions -fno-inline)
    target_link_options(${TARGET} PRIVATE -coverage)
endif()
