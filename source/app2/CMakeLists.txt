set(TARGET app2)
set(SRC main.c)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_SOURCE_DIR}/source
)
target_link_libraries(${TARGET} PRIVATE
    App
    System
)
if(ENABLE_COVERAGE)
    target_compile_options(${TARGET} PRIVATE -O0 -coverage -fno-exceptions -fno-inline)
    target_link_options(${TARGET} PRIVATE -coverage)
endif()