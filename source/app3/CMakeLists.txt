set(TARGET app3)
set(SRC main.c)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_SOURCE_DIR}/source
)
target_link_libraries(${TARGET} PRIVATE
    App
    System
)